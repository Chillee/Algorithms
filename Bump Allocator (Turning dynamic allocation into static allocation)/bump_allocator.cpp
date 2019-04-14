static char buf[450 << 20];
void *operator new(size_t s) {
    static size_t i = sizeof buf;
    assert(s < i);
    return (void *)&buf[i -= s];
}
void operator delete(void *) {}