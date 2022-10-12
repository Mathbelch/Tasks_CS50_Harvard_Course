<h1>Substitution_Cryptography</h1>
<p><b>TASK:</b> Create an algorithm that asks for a <b>substitution key</b>, then read a text file (plain text) and encrypts it using the <b> Monoalphabetic Cipher Method </b>. Finally prints the encrypted text (ciphertext) in an output file.</p>


<p><b>Context:</b><br>
There are a lot of  <a href="https://binaryterms.com/substitution-technique-in-cryptography.html" target="_blank">substitution techniques</a> for cryptography. However, they all consist in the characters present in the original message being replaced by the other characters or numbers or by symbols (key).<br>
The Monoalphabetic Cipher is a technique where the cipher alphabet for each plain text alphabet is fixed, for the entire encryption. That means the first letter of the key will replace A in the plain text. The second letter will replace b, and so on.</p>
<p>As an example, for the following key and words sentence:<br>

<table align="center">
    <tr align="center">
        <th>alphabet</th>
        <th>A</th>
        <th >B</th>
        <th >C</th>
        <th >D</th>
        <th >E</th>
        <th >F</th>
        <th >G</th>
        <th >H</th>
        <th >I</th>
        <th >J</th>
        <th >K</th>
        <th >L</th>
        <th >M</th>
        <th >N</th>
        <th >O</th>
        <th >P</th>
        <th >Q</th>
        <th >R</th>
        <th >S</th>
        <th >T</th>
        <th >U</th>
        <th >V</th>
        <th >W</th>
        <th >X</th>
        <th >Y</th>
        <th >Z</th>
    </tr>
        <tr align="center">
        <td>key</td>
        <td>K</td>
        <td >E</td>
        <td >Y</td>
        <td >W</td>
        <td >O</td>
        <td >R</td>
        <td >D</td>
        <td >A</td>
        <td >B</td>
        <td >C</td>
        <td >F</td>
        <td >G</td>
        <td >H</td>
        <td >I</td>
        <td >J</td>
        <td >L</td>
        <td >M</td>
        <td >N</td>
        <td >P</td>
        <td >Q</td>
        <td >S</td>
        <td >T</td>
        <td >U</td>
        <td >V</td>
        <td >X</td>
        <td >W</td>
    </tr>
</table>

</p>
<br><p align="center">HELLO Word!<br>AOGGJ Ujnw!
<p><b>Constraints:</b>
<ul>
<li>The usage must be by command line argumment, passing the key for cypher;</li>
<li> The key must be a 26 characters sequence, with all alphabetical letters;</li>
<li>Only letters must be altered, and their cases must be maintained (upper or lower);</li>
<li>The plain_text must be read from a txt file and the cypher text must be printed in an output txt file;
</ul>
<br>
