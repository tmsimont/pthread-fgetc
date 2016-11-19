## pthread-fgetc

I wrote this to test the performance of `fgetc()` when muliple threads open up a file for reading at the same time. I'm curious about when and if `fgetc()` can become a bottleneck for multi-threaded programs that are reading from the same file.
