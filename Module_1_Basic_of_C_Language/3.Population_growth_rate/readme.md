<h1>Population Growth</h1>
<p><b>TASK:</b> Create an algorithm that receives the actual population of a specific specie with growth rate shown below, and the final desired population. The program must return the time (in years) that it will take for the population growth proposed.</p>

<p><b>Constraints:</b>
<ul>
<li>The initial population must be at least 9;</li>
<li>The time must be returned in an int value;</li>
</ul> 
</p><br>
<b>Growth Rate per year:</b><br>

$$ Population = population + \frac{population}{3} - \frac{population}{4} $$

<p><b>Tests:</b><br>
<ul>
<li>Start size: 1200, End size: 1300 = Years: 1</li>
<li>Start size: 20, End size: 1 (error), End size: 10 (error), End size: 100 = Years: 20</li>
<li>Start size: -5 (error), Start size: 3 (error), Start size: 9, End size: 5 (error), End size: 18 = Years: 8</li>
<li>Start size: 100, End size: 1000000 = Years: 115</li>
</ul>
</p>
