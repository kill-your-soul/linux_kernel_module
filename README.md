# Linux Kernel Module 

Example of a Linux Kernel Module that write message to file. And program that change parameters of this module.

## Prerequisites
1. [git](https://git-scm.com/)
2. [make](https://www.gnu.org/software/make/)
3. [gcc](https://gcc.gnu.org/)
4. [linux-headers](https://www.kernel.org/doc/html/latest/admin-guide/kernel-parameters.html)

## Installation
    1. Clone repository
    
    ```bash
    git clone https://github.com/kill-your-soul/linux_kernel_module.git
    ```

    2. Build module

    ```bash
    cd linux_kernel_module
    make
    ```

    3. Install module

    ```bash
    make load
    ```

    4. Check module

    ```bash
    sudo dmesg
    ```

    5. Build program

    ```bash
    gcc -o set_params set_params.c
    ```

    6. Run program

    ```bash
    sudo ./set_params
    ```

    