#Introduction
This code compiles against the CRY cosmic ray simulation package:
https://nuclear.llnl.gov/simulation/main.html

It generates cosmic ray vectors, and filters these events according
to the scintillator paddle arrangement and trigger conditions at the
BNL 1 ton tank.

The output is in the form of text files that can be passed to
RAT-PAC using the "external" generator:
"/generator/add external VERTEX:TIME:INPUT"
More details in the RAT-PAC documentation:
http://rat.readthedocs.io/en/latest/generators.html#external


#Compiling

1 - Set environment variable CRYHOME to point at a CRY installation.
2 - Set up a ROOT environment.
3 - Run 'make'.

#Running

Run with:
./BNL1tonTriggeredCosmics <setup file name> <N files> <N events per file> <Output file base name>

 - For an example set up file, see "setupBNL.file"
 - A total of N_files * N_events_per_file events will be generated
 - Name of output files is given by last argument.
