

# thanks to this site
# https://xiayingp.gitbook.io/build_a_os/traps-and-interrupts/untitled-2
# struct trapframe {
#   /*   0 */ uint64 kernel_satp;   // kernel page table
#   /*   8 */ uint64 kernel_sp;     // top of process’s kernel stack
#   /*  16 */ uint64 kernel_trap;   // usertrap()
#   /*  24 */ uint64 epc;           // saved user program counter
#   /*  32 */ uint64 kernel_hartid; // saved kernel tp
#   /*  40 */ uint64 ra;
#   /*  48 */ uint64 sp;
#   /*  56 */ uint64 gp;
#   /*  64 */ uint64 tp;
#   /*  72 */ uint64 t0;
#   /*  80 */ uint64 t1;
#   /*  88 */ uint64 t2;
#   /*  96 */ uint64 s0;
#   /* 104 */ uint64 s1;
#   /* 112 */ uint64 a0;
#   /* 120 */ uint64 a1;
#   /* 128 */ uint64 a2;
#   /* 136 */ uint64 a3;
#   /* 144 */ uint64 a4;
#   /* 152 */ uint64 a5;
#   /* 160 */ uint64 a6;
#   /* 168 */ uint64 a7;
#   /* 176 */ uint64 s2;
#   /* 184 */ uint64 s3;
#   /* 192 */ uint64 s4;
#   /* 200 */ uint64 s5;
#   /* 208 */ uint64 s6;
#   /* 216 */ uint64 s7;
#   /* 224 */ uint64 s8;
#   /* 232 */ uint64 s9;
#   /* 240 */ uint64 s10;
#   /* 248 */ uint64 s11;
#   /* 256 */ uint64 t3;
#   /* 264 */ uint64 t4;
#   /* 272 */ uint64 t5;
#   /* 280 */ uint64 t6;
# };

/*

        * Honestly here magic will going to happen , In this file!!

*/
.section .tramp # this will goto tram sectiom!!
.globl usertrap
.globl uservec
uservec:    
        csrw sscratch, a0
        li a0, 0x3fffff0000  # this value beoongs to the trapfram value calculated from core
        sd ra, 40(a0)
        sd sp, 48(a0)
        sd gp, 56(a0)
        sd tp, 64(a0)
        sd t0, 72(a0)
        sd t1, 80(a0)
        sd t2, 88(a0)
        sd s0, 96(a0)
        sd s1, 104(a0)
        sd a1, 120(a0)
        sd a2, 128(a0)
        sd a3, 136(a0)
        sd a4, 144(a0)
        sd a5, 152(a0)
        sd a6, 160(a0)
        sd a7, 168(a0)
        sd s2, 176(a0)
        sd s3, 184(a0)
        sd s4, 192(a0)
        sd s5, 200(a0)
        sd s6, 208(a0)
        sd s7, 216(a0)
        sd s8, 224(a0)
        sd s9, 232(a0)
        sd s10, 240(a0)
        sd s11, 248(a0)
        sd t3, 256(a0)
        sd t4, 264(a0)
        sd t5, 272(a0)
        sd t6, 280(a0)
        csrr t0, sscratch
        sd t0, 112(a0)
        ld sp, 8(a0)
        ld tp, 32(a0)
        ld t0, 16(a0)
        ld t1, 0(a0)
        sfence.vma zero, zero
        csrw satp, t1
        sfence.vma zero, zero
        jr t0

.globl userret
userret:

        sfence.vma zero, zero
        csrw satp, a0
        sfence.vma zero, zero
        li a0, 0x3fffff0000
        ld ra, 40(a0)
        ld sp, 48(a0)
        ld gp, 56(a0)
        ld tp, 64(a0)
        ld t0, 72(a0)
        ld t1, 80(a0)
        ld t2, 88(a0)
        ld s0, 96(a0)
        ld s1, 104(a0)
        ld a1, 120(a0)
        ld a2, 128(a0)
        ld a3, 136(a0)
        ld a4, 144(a0)
        ld a5, 152(a0)
        ld a6, 160(a0)
        ld a7, 168(a0)
        ld s2, 176(a0)
        ld s3, 184(a0)
        ld s4, 192(a0)
        ld s5, 200(a0)
        ld s6, 208(a0)
        ld s7, 216(a0)
        ld s8, 224(a0)
        ld s9, 232(a0)
        ld s10, 240(a0)
        ld s11, 248(a0)
        ld t3, 256(a0)
        ld t4, 264(a0)
        ld t5, 272(a0)
        ld t6, 280(a0)
        ld a0, 112(a0)
        sret