
header files:
/lib/modules/4.15.0-42-generic/build/include/linux
ubuntu 4.15.0-42 porting:

1.Makefile:
CFLAGS---> EXTRA_CFLAGS [old style]
2.main.c
//#include <linux/config.h>
#include <asm/system.h> --->  #include <asm/switch_to.h>
init_MUTEX(sem); ---> sema_init(sem, 1); 
ioctl ---> unlocked_ioctl;
3.pipe.c
init_MUTEX(sem); ---> sema_init(sem, 1); 
ioctl ---> unlocked_ioctl;
add #include <linux/sched.h>
4.access.c
init_MUTEX(sem); ---> sema_init(sem, 1); 4 place;
ioctl ---> unlocked_ioctl; 4 place;
static spinlock_t scull_u_lock = SPIN_LOCK_UNLOCKED;-->static DEFINE_SPINLOCK(scull_u_lock);
add #include <linux/sched.h>
current->uid ---> current->cred->uid.val;
********************************************************
1.insmod ./scull.ko
2.lsmod will see scull in the 1st line, and also "/sys/module/scull" is created.
"cat /proc/devices" to check the major/minor
3.mkdir  /dev/scull; mknod /dev/scull/scull0 c major 0
then the char devices is there.
 4.chmod +x ./scull_load and run ./scull_load


1. misc-modules:
Makefile : del seq.o jit.o jiq.o silly.o faulty.o kdatasize.o kdataalign.o
2>. jit.c :
	1>. linux/config.h del
	2>. proc_create_data, not create_proc_read_entry
	3>. add header files : slab.h sched.h uaccess.h signal.h
	4>. cat jitimer will crash the pc, so the later tasklet also not verified.--> TBD
	5>. init_timer is outdate; -> timer_setup/from_timer in timer.h  TBD
3>. jiq.c : 
	1>. INIT_WORK change : search 'work_struct' in workqueue.h 's changelist;
	2>. refer 'linux/kernel/drivers/iio$ vi ./imu/st_lsm6ds3h/st_lsm6ds3h_trigger.c +243'
	3>. schedule_delayed_work in workqueue.h --->TBD
	4>. DECLARE_TASKLET  --> keep 'long'
4>. seq.c +97 : change api
5>. faulty.c the intended overflow can be detected by compiler and then errored! --> TBD
6>. kdatasize.c : OK; kdataalign.c some;
7>. silly.c : change f_inode;

2. scull:
Makefile: CFLAGS -> ccflags-y
staff -> lpq;
scullpipe : as shown in my polltest-pipe.c; 'echo sth > scullpipe' then you can get it from here;

3. short:
1> Makefile: CFLAGS -> ccflags-y
2> linux/config.h del
3> filp->f_dentry->d_inode  --> filp->f_inode;
4> #include <linux/sched/signal.h> // lpq add for signal_pending
5> SA_INTERRUPT -> del
	SA_SHIRQ -> IRQF_SHARED
6> irqreturn_t short_sh_interrupt(int irq, void *dev_id, struct pt_regs *regs) : del 3rd parameter;
7>. DECLARE_TASKLET  --> keep 'long'
8>. INIT_WORK change : 'work_struct' ;
9> load with tasklet=1/wq=nonzero/shared=1/irq=x/probe=x/
sudo ./short_load ; sudo ./short_load use_mem=1 base=0xb7ffffc0 ;
dd if=/dev/short0 bs=1 count=1 |od -t x1 :

4. misc-progs:
Makefile: del setlevel
asm/io.h -> sys/io.h
add scullsingleTest.c/sculluidTest.c
1>. scullsingle : './scullsingleTest /dev/scullsingle'
2>. sculluid :
different uid: MobaXterm remote log in as daniel/1-6; and run './sculluidTest /dev/sculluid' 1 after 1;
wuid: MobaXterm remote log in as daniel/1-6; run './sculluidTest /dev/scullwuid' 1 after 1; 
	the later one open only after the first one release : wait queue;
3>. scullpriv: run 'echo azzz > scullpriv; cat scullpriv' in different tty, their contents are indepedent;
how to make different tty: different terminal;
4>. "load50 xx" : "ps ax |grep load" ;
5>. asynctest.c : 'SIGIO' will triggered by every input; async notification;
6>. mapper.c/mapcmp : mmap from a file;
7>. nbtest : nonblock input/output;
8>. inp/outp : "sudo ./inp 1DE" (addrInHex); 64bit act as non-386 and always return ff;

