#! /usr/bin/env python3

import requests
import sys
from subprocess import call
import yaml
import os
import json
import argparse

COLOR_LIGHT_CYAN = "\033[1;36m"
COLOR_END = "\033[0m"

parser = argparse.ArgumentParser(
    description='Download all gists for a given user')
parser.add_argument('-v', '--verbose', help="be verbose", action='store_true')
parser.add_argument(
    '-f', '--file', help="configuration file", default="gists.yaml")
parser.add_argument('user', nargs='?', help="username")

args = parser.parse_args()

if args.verbose:
    print("args={}".format(args))

config = {}
if os.path.isfile(args.file):
    with open(args.file) as f:
        config = yaml.load(f)

# if a username is given, keep only its gists in the configuration, if any
if args.user:
    config = {args.user: config.get(args.user, {})}

if args.verbose:
    print("config={}".format(config))

# get the gists
for user, names in config.items():

    r = requests.get('https://api.github.com/users/{0}/gists'.format(user))

    if r.status_code != 200:
        print("error with user {}: {}".format(user, r))
        continue

    print("Found {} gist(s)".format(len(r.json())))

    # for each gist of the user
    for i in r.json():
        if args.verbose:
            print()
            print(json.dumps(i, indent=4))

        id = i['id']
        if names and id in names:
            id = names[id]

        sys.stdout.write(COLOR_LIGHT_CYAN + "Updating " +
                         id + " ... " + COLOR_END)
        sys.stdout.flush()

        folderName = i['description']
        if os.path.isdir(id):
            call(['git', '-C', id, 'pull', folderName])
        else:
            call(['git', 'clone', i['git_pull_url'], folderName])

        description_file = os.path.join(folderName, 'description.txt')
        with open(description_file, 'w') as f:
            f.write('{0}\n'.format(i['description']))

        # data_file = os.path.join(id, 'data.json')
        # with open(data_file, 'w') as f:
        #    json.dump(i, f, indent=4)
