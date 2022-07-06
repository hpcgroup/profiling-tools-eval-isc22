# Building Tools
## Caliper Spack build line
```
caliper@2.6.0%gcc@8.3.1+adiak~cuda+fortran+gotcha~ipo+libdw~libpfm+libunwind+mpi+papi+sampler+shared~sosflow build_type=RelWithDebInfo cuda_arch=none arch=linux-rhel7-broadwell
```

# HPCToolkit Spack build line
```
hpctoolkit@2021.05.15%gcc@8.3.1~all-static~cray~cuda~debug+mpi+papi~rocm+viewer arch=linux-rhel7-broadwell
```

# Score-P build line
```
./configure --prefix=<PREFIX_PATH> --with-mpi=openmpi --with-libunwind=<LIBUNWIND_PATH> --with-pdt=<PDT_PATH> --with-nocross-compiler-suite=gcc
```

# TAU Spack build line
```
tau@2.30.1%gcc@8.3.1~adios2+binutils~comm~craycnl~cuda+elf+fortran~gasnet+io~level_zero+libdwarf+libunwind~likwid+mpi~ompt~opari~opencl~openmp+otf2+papi+pdt~phase~ppc64le~profileparam+pthreads~python~rocm~rocprofiler~roctracer~scorep~shmem~sqlite~x86_64 arch=linux-rhel7-broadwell
```

# AMG

## Build AMG with one of the profiling tools
More details can be found under `AMG/Makefile.include` and `AMG/test/Makefile`.

```
make TOOL=WITH_<tool_name> <TOOL_NAME>_DIR=$(spack location --install-dir <tool_name>)
```

#### Example:
```
make TOOL=WITH_CALIPER CALIPER_DIR=$(spack location --install-dir caliper) 
```

`WITH_<TOOL_NAME>` can be `WITH_CALIPER, WITH_HPCTOOLKIT, WITH_SCOREP, WITH_TAU_SOURCE, WITH_TAU_COMPILER`.

Set `TAU_MAKEFILE` for TAU. Example: `TAU_MAKEFILE=$(TAU)/Makefile.tau-papi-mpi-pthread-pdt` 

## AMG parameters

#### 64 processes
```
srun -n 64 <executable> -problem 2 -n 100 100 100 -P 4 4 4
```
#### 128 processes 
```
srun -n 128 <executable> -problem 2 -n 100 100 100 -P 4 4 8
```
#### 256 processes
```
srun -n 256 <executable> -problem 2 -n 100 100 100 -P 4 8 8
```
#### 512 processes
```
srun -n 512 <executable> -problem 2 -n 100 100 100 -P 8 8 8
```

## AMG executables
Name of the executable: `amg<tool_name>`

```
Caliper: amgcaliper.exe
HPCToolkit: amghpctoolkit.exe
Score-P: amgscorep.exe
TAU: amgtau-source.exe
TAU: amgtau-compiler.exe
Without: amg.exe
```

# LULESH

## Build LULESH with one of the profiling tools
More details can be found under `/caliper-examples/apps/LULESH/CMakeLists.txt`

Add the following cmake commands:
```
-DWITH_MPI=On -DWITH_OPENMP=Off -DCMAKE_CXX_FLAGS="-g -O3" -DWITH_<TOOL_NAME>
```
`WITH_<TOOL_NAME>` can be `WITH_CALIPER, WITH_HPCTOOLKIT, WITH_SCOREP, WITH_TAU_SOURCE, WITH_TAU_COMPILER (add -optCompInst)`.

Use compiler wrappers for Score-P `(scorep-mpicxx)` and TAU `(tau_cxx.sh)`

## LULESH parameters
#### 64 processes
```
srun -n 64 <executable> -i 500 -p -s 64
```
#### 128 processes
```
srun -n 125 <executable> -i 500 -p -s 64
```
#### 256 processes
```
srun -n 216 <executable> -i 500 -p -s 64
```
#### 512 processes
```
srun -n 512 <executable> -i 500 -p -s 64
```

## LULESH executables
Name of the executable: `lulesh-<tool_name>2.0`

```
Caliper: lulesh-caliper2.0
HPCToolkit: lulesh-hpctoolkit2.0
Score-P: lulesh-scorep2.0
TAU (source inst): lulesh-tau-source2.0
TAU (compiler inst): lulesh-tau-compiler2.0
Without: lulesh2.0
```

# Quicksilver

## Build Quicksilver with one of the profiling tools
More details can be found under `/caliper-examples/apps/Quicksilver/src/Makefile`.

```
make TOOL=HAVE_<TOOL_NAME> <TOOL_NAME>_DIR=$(spack location --install-dir <tool_name>)
```

Example:
```
make TOOL=HAVE_HPCTOOLKIT HPCTOOLKIT_DIR=$(spack location --install-dir hpctoolkit)
```

`HAVE_<TOOL_NAME>` can be `HAVE_CALIPER, HAVE_HPCTOOLKIT, HAVE_SCOREP, HAVE_TAU_SOURCE, HAVE_TAU_COMPILER.`

Set `TAU_MAKEFILE` for TAU. Example: `TAU_MAKEFILE=$(TAU)/Makefile.tau-papi-mpi-pthread-pdt`.

## Quicksilver parameters
#### 64 processes
```
srun -n 64 <executable> -X 16 -Y 16 -Z 16 -x 16 -y 16 -z 16 -I 4 -J 4 -K 4 -n 3604480 -N 700
```
#### 128 processes
```
srun -n 128 <executable> -X 32 -Y 16 -Z 16 -x 32 -y 16 -z 16 -I 8 -J 4 -K 4 -n 7208960 -N 700
```
#### 256 processes
```
srun -n 256 <executable> -X 32 -Y 32 -Z 16 -x 32 -y 32 -z 16 -I 8 -J 8 -K 4 -n 14417920 -N 700
```
#### 512 processes
```
srun -n 512 <executable> -X 32 -Y 32 -Z 32 -x 32 -y 32 -z 32 -I 8 -J 8 -K 8 -n 28835840 -N 700
```

## Quicksilver executables
Name of the executable: `qs<tool_name>.exe`

```
Caliper: qscaliper.exe
HPCToolkit: qshpctoolkit.exe
Score-P: qsscorep.exe
TAU (source inst): qstau-source.exe
TAU (compiler inst): qstau-compiler.exe
Without: qs.exe
```
