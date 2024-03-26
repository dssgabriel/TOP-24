# MYCHP203 — Parallel Optimization Techniques, Spring 2024

## Course Information

### Descrition & Objectives

This class provides an overview of common optimization techniques in parallel & distributed execution contexts. It covers the technical foundations of how to leverage tools such as compiler directives, debuggers, and profilers to optimize HPC applications. By the end of the course, students should have expertise on the main performance issues tied to parallelization: how to identify and fix them.

The students are expected to learn and understand:
- parallel and distributed architectures
- performance analysis methodology: using static and dynamic analysis tools to pinpoint performance hotspots and characterize the performance profile of HPC applications;
- quantitative and qualitative analysis of the main parallel bottlenecks: communication & synchronization overhead, load balancing, network saturation;
- advanced use of compiler builtins, OpenMP directives and intrinsics;
- leveraging parallel debugging tools (DDT, Marmot, Thread Checker), as well as profilers (Tau, Scalasca, MAQAO, Kojak, Vampir, ...).

### Lectures

Tuesday, 13:45 - 17:00 CET, CN2, Rabelais building, Guyancourt campus

### Lab sessions

Tuesdays, 9:30 - 12:45 CET, CN2, Rabelais building, Guyancourt campus

### Examination

This class is evaluated for the 1st Year of the Paris-Saclay University Master's Degree in High Performance Computing & Simulation.
| | |
|-----------------------------------------------|--------------------------------------------------------------|
| **ECTS Credits**                              | 3 credits (out of 30 semester credits)                       |
| **Examiner(s)**                               | H. Taboada, G. Dos Santos                                    |
| **Mode of examination**                       | One written exam, one project                                |
| **Additional information on the examination** | % of each exam for the course grade: _TBD_                   |
| **Written aids**                              | None                                                         |


## Staff Information

| **Role** | **Name** | **E-Mail** |
|---|---|---|
| **Instructor** | Hugo Taboada | hugo.taboada@cea.fr |
| **Teaching Assistant** | Gabriel Dos Santos | gabriel.dos-santos@uvsq.fr, gabriel.dossantos@cea.fr |

Please contact the instructor or TA for any questions regarding the course.   
E-mails can be sent in either French or English at your convenience.

Please be mindful when sending e-mails. If it is your first contact with the instructor or TA, don't forget to present yourself. Try to clearly and concisely express your problem. Detail the steps you have already taken and what you have tried.

> [!WARNING]
> For filtering reasons and easier e-mail management from the teaching staff, please make sure that all e-mail subjects are prefixed with:    
> `[M1CHPS-TOP] <your subject>`
>
> Any e-mail written in an informal manner or without proper syntax will be dismissed.

Here are some links to correctly write an e-mail in a professional setting:
- https://www.grammarly.com/blog/professional-email-in-english/
- https://www.grammarly.com/blog/formal-email/

---

> [!NOTE]
> In addition to e-mail, students can also reach the TA on Discord (handle: **@gabrl**), either by Private Message or through the Master CHPS server: [invite link](https://discord.gg/9FNCtn326c).


## Material

### Lectures

Each lecture will be made available _after_ it has been given.

### Lab sessions

Lab sessions are not graded, though they remain mandatory. Any absence shall be justified to the administration and the TA.   
Exercises are corrected during class, and corrections will _not_ be given.

### Resources

> [!TIP]
> Valuable resources for this course will be added here.

Build systems:
- A guide on [Modern CMake](https://cliutils.gitlab.io/modern-cmake/)
- [Ninja build system](https://ninja-build.org/)

C Programming language:
- [Modern C](https://inria.hal.science/hal-02383654) by Jens Gustedt (researcher at INRIA Strasbourg and ISO C standards committee member)
- [Latest draft of the ISO C standard](https://open-std.org/jtc1/sc22/wg14/www/docs/n3220.pdf) (as of 2024-03-26)

Computer Architecture:
- [What every programmer should know about memory](https://people.freebsd.org/~lstewart/articles/cpumemory.pdf)
- [Computer Architecture: A quantitative approach](https://dl.acm.org/doi/book/10.5555/1999263)
- [C++ on sea 2023, a talk by JF Bastien - \*(char\*)0 = 0;](https://youtu.be/dFIqNZ8VbRY) (treats about memory hierarchy: caches, TLB, virtual/physical memory)

Memory:
- [Kokkos tutorial slides](https://github.com/kokkos/kokkos-tutorials/blob/main/Intro-Full/Slides/KokkosTutorial_ORNL20.pdf) (specifically slides on memory layout, slides 74-84)
- [Cache coherency protocols](https://en.wikipedia.org/wiki/Cache_coherency_protocols_(examples))

