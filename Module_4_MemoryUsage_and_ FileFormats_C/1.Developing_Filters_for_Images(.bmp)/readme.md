<h1>Elections Algorithms: Plurality!</h1>
<p><b>TASK:</b> Create an algorithm - in C language - able to run a <b>plurality election</b>, showing the winner at the end. Make sure to take a look at the constraints below.</p>

<p><b>Context:</b><br>
One of the simplest ways to realize an election is through the <a href="https://aceproject.org/main/english/bd/bda01a.htm" target="_blank">Plural Voting Method</a>, also know as <i>the first come</i> or <i>the winner takes all</i> method. In a plurality voting each voter can vote for one and only candidate. At the end of the election, after all votes had been collected, the candidate with the most votes wins the election.</p>
<br>
<b>Constraints:</b>
<ul>
<li>The usage must be by command line argumment, passing the name of the candidates on the election. The maximum number of candidates is 9;</li>
<li>Your algorithm must use a struct called cadidate to keep the candidate's names and number of votes;</li>
<li>Your algorithm must have 2 functions: </li>
    <ul>
    <li>One for receiving each vote, checking its validity, and computing the vote. If the vote is not valid, it must be disconsidered, and the algorithm must skip to the next vote.</li>
    <li>Anothe one to check and print the winner of the election. We must consider the possibility of a tie, where there may be - in this case - more than one winner. 
    </ul>
</ul>








