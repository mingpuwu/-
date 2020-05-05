# strace: Process 111788 detached
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 42.56    0.002419         161        15           clone
 22.77    0.001294          62        21           mprotect
 22.29    0.001267          53        24           mmap
  1.81    0.000103          26         4           fstat
  1.30    0.000074          74         1           munmap
  1.28    0.000073          24         3           brk
  1.25    0.000071          36         2           rt_sigaction
  1.04    0.000059          30         2           write
  0.86    0.000049          16         3           close
  0.83    0.000047          47         1           set_tid_address
  0.76    0.000043          43         1           nanosleep
  0.76    0.000043          14         3           openat
  0.70    0.000040          10         4         4 access
  0.51    0.000029          15         2           read
  0.37    0.000021          21         1           set_robust_list
  0.35    0.000020          20         1           arch_prctl
  0.35    0.000020          20         1           prlimit64
  0.21    0.000012          12         1           rt_sigprocmask
  0.00    0.000000           0         1           execve
------ ----------- ----------- --------- --------- ----------------
100.00    0.005684                    91         4 total