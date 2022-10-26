<h1>Changing a WAV file volume!</h1>
<p><b>TASK:</b> Create an algorithm - in C language - able to run change the volume of an audio file with .wav extension. Your algorith must receive the input and output files' names and extensions by command line argument.</p>

<p><b>Context:</b><br>
WAV, known for <a href="https://docs.fileformat.com/audio/wav/" target="_blank">WAVE (Waveform Audio File Format)</a>, is a subset of Microsoft’s Resource Interchange File Format (RIFF) specification for storing digital audio files. In a WAV file, audio is stored as a sequence of data (integers of 2 bytes) that represents the audio signal in a specific time. Since the signal is represented by an int, we can alter its number to increase or decrease the audio volume. WAV files can be regonized by their header (44 bytes with informations about the file).  </p>

<p><b>Test:</b> Considering the input file as the original one, the file output2 has the volume increased 2 times, while the file output3 has the volume decreased in half.</p>








