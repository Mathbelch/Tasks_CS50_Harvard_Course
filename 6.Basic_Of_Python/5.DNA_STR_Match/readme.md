<h1>DNA - STR Match</h1>
<p><b>TASK:</b> Create an algorithm that receives as input a DNA sample sequence (.txt file) and a DNA database (.csv file) containing the names of people and their STR repeated sequences numbers. The output of the algorithm must be the name of the person that matches the sample sequence, according to their Short Tandem Repeats (STRs) numbers.</p>

<p><b>Rules:</b>
<ul>
<li>Both .csv and .txt files must be passed as command line arguments:<br> <i>python dna.py databases/nameData.csv sequences/sampleNumber.txt </i>;</li>
<li>Consider the .txt files as single strings with the letters of the nucleotides;</li>
<li>Consider the .csv files as tables containing the header (name, STRs) in the first row and the people's informations on the others.</li>
</ul> 
</p><br>

<p><b>CONTEXT:</b><a href="https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5054066/#:~:text=Short%20tandem%20repeats%20(STRs)%2C,prokaryotes%20and%20eukaryotes%2C%20including%20humans." type="_blank"> Short Tandem Repeats (STRs)</a> are short repeated sequences of DNA (2-6 bp) that account for approximately 3% of the human genome and are extremely useful in applications as the identification of individuals in Forensic DNA profiling since the number of repeat units is highly variable among individuals, which offers a high power of discrimination when analyzed for identification purposes. 
Using multiple STRs instead of just one can improve DNA profiling accuracy, as the example of <a href="https://www.fbi.gov/how-we-can-help-you/dna-fingerprint-act-of-2005-expungement-policy/codis-and-ndis-fact-sheet" type="_blank">CODIS</a>, the FBI's DNA database, that uses 20 different STRs as part of its DNA profiling process.</p>





