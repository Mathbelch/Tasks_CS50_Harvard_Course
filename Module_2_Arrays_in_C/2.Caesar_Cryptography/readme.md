<h1>Caesar_Cryptography</h1>
<p><b>TASK:</b> Create an algorithm that receives a key, then read a text file (plain text) and encrypts it using the <b> Caesar Method </b>, then prints the encrypted text (ciphertext) in an output file.</p>

<p><b>Context:</b><br>
The <a href="http://practicalcryptography.com/ciphers/caesar-cipher/" target="_blank">Caesar criptography method </a>consists in encrypt messages by “rotating” each letter in <b>k</b> positions, where K is the <b>Key</b>. That means each letter in the plain text will be replaced by the letter <b>k</b> position in front of it, alphabetically.
<br>
Considering there are 26 letters in the alphabet, it is important to make the algorithm in a way that it returns back to the beginning if <b>k</b> passes it through. The formula below may help:</p>
<p align="center"> CypherChar = (PlainChar + key) % (26) </p>
<p><b>Constraints:</b>
<ul>
<li>The usage must be by command line argumment, passing the key for cypher;</li>
<li>The key must be a number greater than 0;</li>
<li>Only letters must be altered, and their cases must be maintained (upper or lower);</li>
<li>The plain_text must be read from a txt file and the cypher text must be printed in an output txt file;</li>
</ul>
</p>
<br>

<br>
<p align="center"><b><u>Expected results for each test.txt file:</u></b>
<table align="center">
    <tr align="center">
        <th>Test</th>
        <th >Key</th>
        <th align="center">Result</th>
    </tr>
    <tr>
        <td rowspan="2">1</td>
        <td >1</td>
        <td align="center">IFMMP</td>
    </tr>
    <tr>
        <td>13</td>
        <td align="center">URYYB</td>
    </tr>
    <tr>
        <td rowspan="2">2</td>
        <td>13</td>
        <td align="center">uryyb, jbeyq</td>
    </tr>
    <tr>
        <td>17</td>
        <td align="center">yvccf, nficu</td>
    </tr>
            <td rowspan="2">3</td>
        <td>13</td>
        <td align="center">or fher gb qevax lbhe Binygvar</td>
    </tr>
    <tr>
        <td>8</td>
        <td align="center">jm aczm bw lzqvs gwcz Wditbqvm</td>
    </tr>
    </table>
    </p>







