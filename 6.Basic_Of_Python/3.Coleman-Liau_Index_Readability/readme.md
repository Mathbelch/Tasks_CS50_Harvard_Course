<h1>Readability</h1>
<p><b>TASK:</b> Create an algorithm that reads a text file and return its readability level, according to the <b> Coleman-Liau Index </b>.</p>

<p><b>Context:</b><br>
The <a href="https://en.wikipedia.org/wiki/Coleman%E2%80%93Liau_index" target="_blank">Coleman-Liau Index </a> is a readability test designed by Meri Coleman and T. L. Liau to gauge the understandability of a text. <br>
This Index is used to assign correctly the texts during education process, since students from different grades are able to read texts with different complexity.<br>
The process is pretty simple, we must know the number of letter in the text, also the number of words and the number of sentences. <br>
Finally, we apply these values into the formula below and the rounded returned value will be the grade for which this text is indicated. </p>

$$ Coleman–Liau-index = (0.0588 * L) - (0.296 * S) - 15.8 $$
<p>
<ul>
<li>L: Average number of letters per 100 words;</li>
<li>S: Average number of sentences per 100 words;</li>
</ul>
<br>
&nbsp;<b>Obs:</b> The Coleman Liau Index varies from <em>Before Grade 1</em> to <em>Grade 16+</em>.
</p>






