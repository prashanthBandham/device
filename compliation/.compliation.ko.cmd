cmd_/home/prashanth/device/compliation/compliation.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000  --build-id  -T ./scripts/module-common.lds -o /home/prashanth/device/compliation/compliation.ko /home/prashanth/device/compliation/compliation.o /home/prashanth/device/compliation/compliation.mod.o;  true