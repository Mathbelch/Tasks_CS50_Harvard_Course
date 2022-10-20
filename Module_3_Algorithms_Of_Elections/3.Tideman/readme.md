<h1>Elections Algorithms: Ranked Choice Voting System & Tideman!</h1>
<p><b>TASK:</b> Create an algorithm - in C language - able to run a <b>Tideman Election</b>, showing the winner at the end. Make sure to take a look at the constraints below.</p>

<p><b>Context:</b><br>
In a <a href="https://fairvote.org/our-reforms/ranked-choice-voting/" target="_blank">
Ranked Choice Voting System</a> each voter makes a rank of the candidates (instead of only voting for the prefered one). Its use instead of a simple plurality method allows an election that would end in a tie for plurality votes to have a winner. Also, another advantage is that by considering ranked preferences, a voting system may be able to choose a winner that better reflects all voters' preferences.</p>
<p>Among the different variations of ranked choice voting systems is the <a href="https://en.wikipedia.org/wiki/Ranked_pairs" target="_blank">
Tideman</a>, or <i> ranked pairs method </i>, which ensure that the winner of the election - if there's one - will be the <b>Condorcet Winner</b>.</p>
<p>The <b>Condorcet Winner</b> of a election is the candidate who would have won the election if it was a direct confront with other candidate. That means, in any situation where there would be only 2 candidates, this candidate would win.</p>
<p>The <b>Tideman Method</b> consists on building an abstract graph with the candidates being the entities (or boxes) of this graph. When there's an arrow pointing from one candidate (box/entity) to another, it means that the candidate who is the source of the arrow would win a direct confront against the candidate who is in the point of the arrow. Finally, once the graph is done (all votes had been calculated and all arrows had been included), the candidate who is in the called <b>Main Source Position</b> (the one with no arrows pointed to) is the <b>Condorcet Winner</b> of the election.</p> 
<p>There are two possible ways to conduct the graph building process for the Tideman method. In the simpler one (just adding all the arrows) we may end up with no source candidate in the graph. That would mean there isn't a Condorcet winner. To garantee a winner, we can follow an approach where during the process of building the graph we check - before adding a new arrow - if that would creat a cycle. If it would, then we do not put this arrow.</p>
<br>
<p>Basically, the Tideman Method consists of three major steps:
<ol>
    <li><b>Tally:</b> Once all voters' preferences had been received, we check - for each pair of candidates - who is the prefered one and also its margin of victory;</li>
    <li><b>Sort:</b> The candidates pairs must then be sorted by decreased victory force (considering the winner's margin);</li>
    <li><b>Lock:</b> Following the victory force order (from highest to lowest) we know start adding the arrows to the graph. Each arrow we add is locked in the graph, so it can not be removed. An arrow must not be included if it creates a cycle. At the end, we find the graph source!</li>
</ol>
<br>
<b>Constraints:</b>
<ul>
    <li>The usage must be by command line argumment, passing the name of the candidates on the election. The maximum number of candidates is 9;</li>
    <li>Your algorithm must use a struct called pair to keep track of the winner and loser of each candidates' pair, ;</li>
    <li>Your algorithm must use an array called preferences[][] to keep track of each voter's preferences rank;</li>
    <li>Your algorithm must use a boolean array called locked[][] that will represent the abstract tideman graph, where locked[i][j] marked as true means the candidate i points a locked arrow to candidate j;</li>
    <li>Your algorithm must have at least these 6 functions: 
        <ul>
            <li>Vote: called for each voter, it must check if the name given is valid and then save the voter's preferences;</li>
            <li>Recorde_preferences: called for each voter, it must update the global rank with the voter's preferences;</li>
            <li>Add_pairs: it must fill the pair array with the winner and looser for each pair. A pair with a tie must not be added;</li>
            <li>Sort_pairs: it must sort the pair matrix from the higher to the lower victory force. If more than one pair has the same victory force, the order doesn't matter</li>
            <li>Lock_pairs: it must creat the abstract graph of pairs, respecting the victory force of the pairs and checking for the possibility of creating a cycle;</li>
            <li>Print_winner: it must finally print the name of the condorcet winner (graph source);</li>
        </ul></li>
</ul>








