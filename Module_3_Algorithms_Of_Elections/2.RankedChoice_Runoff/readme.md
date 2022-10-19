<h1>Elections Algorithms: Ranked Choice Voting System & RunOff!</h1>
<p><b>TASK:</b> Create an algorithm - in C language - able to run a <b>Runoff Election</b>, showing the winner at the end. Make sure to take a look at the constraints below.</p>

<p><b>Context:</b><br>
In a <a href="https://fairvote.org/our-reforms/ranked-choice-voting/" target="_blank">
Ranked Choice Voting System</a> each voter makes a rank of the candidates (instead of only voting for the prefered one). Its use instead of a simple plurality method allows an election that would end in a tie for plurality votes to have a winner. Also, another advantage is that by considering ranked preferences, a voting system may be able to choose a winner that better reflects all voters' preferences.</p>
<p>Among the different variations of ranked choice voting systems is the <a href="https://archive3.fairvote.org/reforms/instant-runoff-voting/how-instant-runoff-voting-works/" target="_blank">
Instant Runoff</a>, where the election may need more than 1 turn to find the most appropriate winner. At the end of the first turn, if no candidate has won (it must have more than 50% of votes - 1°Rank), the candidate with the fewest number of votes is eliminated and the voters who had chosen this eliminated candidate as their 1°Rank, now have their 2°Rank considered, so the second turn begins. This movement goes cycling until there's a winner or a tie (all candidates have the same number of votes).</p>
<br>
<b>Constraints:</b>
<ul>
<li>The usage must be by command line argumment, passing the name of the candidates on the election. The maximum number of candidates is 9;</li>
<li>Your algorithm must use a struct called cadidate to keep the candidate's names and number of votes, in adition to a bool value to indicate if the candidate is eliminated or not;</li>
<li>Your algorithm must use an array called preferences[][] to keep track of ....;</li>
<li>Your algorithm must have 5 functions: </li>
    <ul>
    <li>Tabulate: must check voters' preferences and calculate the amount of votes for each candidate at each turn;</li>
    <li>Print winner: must print the winner of the election when there's one. It must be called at the end of each turn;</li>
    <li>Find min: If there's no winner at the end of the turn, this function will be called to find how many votes the candidate with the fewest number of votes received;</li>
    <li>Is tie: must check if there is a tie (all candidates receiived the min value of votes).</li>
    <li>Eliminate: if there is no tie; this function must 'eliminate' the candidate(s) with the min value votes;</li>
    </ul>
</ul>








