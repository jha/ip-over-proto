#include "config.h"
#ifdef CONFIG_ENABLE_HWCRC
#include <smmintrin.h>
#endif /* CONFIG_ENABLE_HWCRC */
#include "tuple.h"

/* Use the hardware accelerated CRC for x86_64 platforms */
#ifdef CONFIG_ENABLE_HWCRC
tuple_hash_t
tuple_compute_hash(struct tuple *tpl)
{
    tuple_hash_t th;

    th = _mm_crc32_u32(0, tpl->saddr);
    th = _mm_crc32_u32(th, tpl->daddr);
    th = _mm_crc32_u16(th, tpl->sport);
    th = _mm_crc32_u16(th, tpl->dport);

    return th;
}
#endif /* CONFIG_ENABLE_HWCRC */

/* Use softare-based CRC hashing */
#ifndef CONFIG_ENABLE_HWCRC
tuple_hash_t
tuple_compute_hash(struct tuple *tpl)
{
    UNUSED(tpl);
    return 0;
}
#endif /* CONFIG_ENABLE_HWCRC */
