#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <inttypes.h>
#include <errno.h>

int check_normal(void);
int check_zero_alignment(void);
int check_nonpowerof2_alignment(void);

int main(void) {
    bool error = false;

    if (check_normal() < 0) {
        error = true;
    }

    if (check_zero_alignment() < 0) {
        error = true;
    }

    if (check_nonpowerof2_alignment() < 0) {
        error = true;
    }

    return error ? EXIT_FAILURE : EXIT_SUCCESS;
}

int check_normal(void) {
    const size_t alignment = 0x4000;
    const size_t mask = alignment - 1;

    static_assert((alignment & mask) == 0, "alignment must be a power of 2");

    void *p = aligned_alloc(alignment, alignment);

    if (p == NULL) {
        perror("aligned_alloc");
        return -1;
    }

    uintptr_t addr = (uintptr_t) p;

    free(p);
    p = NULL;

    bool aligned = ((addr & mask) == 0);

    printf("addr (%#"PRIxPTR") is%s aligned\n", addr, aligned ? "" : " NOT");

    return aligned ? 1 : -1;
}

int check_zero_alignment(void) {
    errno = 0;

    void *p = aligned_alloc(0, 4);

    int saved_errno = errno;

    uintptr_t addr = (uintptr_t) p;

    if (p != NULL) {
        free(p);
        p = NULL;

        if (saved_errno == 0) {
            printf("%s: non-null (%#"PRIxPTR"); no error\n", __func__, addr);
            return 1;
        } else {
            printf("%s: non-null (%#"PRIxPTR"); unexpected error %d\n", __func__, addr, saved_errno);
            return -1;
        }
    } else {
        if (saved_errno == EINVAL) {
            printf("%s: null; EINVAL\n", __func__);
            return 0;
        } else {
            printf("%s: null; unexpected error %d\n", __func__, saved_errno);
            return -2;
        }
    }
}

int check_nonpowerof2_alignment(void) {
    errno = 0;

    void *p = aligned_alloc(0x440, 4);

    int saved_errno = errno;

    uintptr_t addr = (uintptr_t) p;

    if (p != NULL) {
        free(p);
        p = NULL;

        if (saved_errno == 0) {
            printf("%s: non-null (%#"PRIxPTR"); no error\n", __func__, addr);
            return 1;
        } else {
            printf("%s: non-null (%#"PRIxPTR"); unexpected error %d\n", __func__, addr, saved_errno);
            return -1;
        }
    } else {
        if (saved_errno == EINVAL) {
            printf("%s: null; EINVAL\n", __func__);
            return 0;
        } else {
            printf("%s: null; unexpected error %d\n", __func__, saved_errno);
            return -2;
        }
    }
}

