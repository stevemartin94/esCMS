	</article>
	</div>
	<footer>
		Design &amp; Coding &copy; 
		<?php
		$time = microtime();
		$time = explode(' ', $time);
		$time = $time[1] + $time[0];
		$finish = $time;
		$total_time = round(($finish - $start), 4);
		
		echo date("Y")." by Stefan Wietreich"; 
		echo ' | Seite generiert in '.$total_time.' Sekunden | '."\n";
		
		if($_SERVER['REQUEST_URI'] == '/' or $_SERVER['REQUEST_URI'] == '/index.php' or $_SERVER['REQUEST_URI'] == '/index.html' or $_SERVER['REQUEST_URI'] == '/?style=mobile' or $_SERVER['REQUEST_URI'] == '/?style=desktop')
		{
			if($style == mobile)
			{
				echo '<a href="/?style=desktop">Desktop-Version anzeigen</a>';
			}
			else
			{
				echo '<a href="/?style=mobile">mobile Version anzeigen</a>';
			}
		}
		else
		{
			if($style == mobile)
			{
				echo '<a href="'.$_SERVER['REQUEST_URI'].'&amp;style=desktop">Desktop-Version anzeigen</a>';
			}
			else
			{
				echo '<a href="'.$_SERVER['REQUEST_URI'].'&amp;style=mobile">mobile Version anzeigen</a>';
			}
		}
		
		$datei = fopen("includes/counter.inc","r+");
		$counterstand = fgets($datei, 10);
		if($counterstand == "")
		{
  			$counterstand = 0;
		}
		$counterstand++;
		echo ' | Aufrufe: '.$counterstand;
		rewind($datei);
		fwrite($datei, $counterstand);
		fclose($datei);
		?> 
		 | <a href="#wrap">nach oben</a>
		<p>
    		Valides <a href="http://validator.w3.org/check?uri=referer">HTML5</a> und 
    		<a href="http://jigsaw.w3.org/css-validator/check/referer?profile=css3">CSS3</a>
  		</p>
	</footer>
	</div>
	</body>
</html>