#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <inttypes.h>

const size_t alignment = 0x4000;

int main(void) {
    const size_t mask = alignment - 1;

    static_assert((alignment & mask) == 0, "alignment must be a power of 2");

    void *p = aligned_alloc(alignment, 2 * alignment);

    if (p == NULL) {
        perror("aligned_alloc");
        return EXIT_FAILURE;
    }

    uintptr_t addr = (uintptr_t) p;

    free(p);
    p = NULL;

    printf("addr is %#08"PRIxPTR"\n", addr);

    bool aligned = ((addr & mask) == 0);

    printf("addr is%s aligned\n", aligned ? "" : " NOT");

    return aligned ? EXIT_SUCCESS : EXIT_FAILURE;
}
