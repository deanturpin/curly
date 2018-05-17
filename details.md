The curl library essentially implements ```popen()``` by piping the results of
calling ```curl``` via ```system()``` and piping the results to a temporary
file. The file is then opened and the results are passed back to the calling
program. This approach has the advantage that the developer can view the results
outside of the programme and known responses can be injected during unit test.
