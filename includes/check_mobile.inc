<?php

function check_mobile() {
  $agents = array(
    'iPhone', 'Android', 'iPod', 'Windows Phone',
    'Windows CE', 'Pocket', 'Mobile',
    'Portable', 'Smartphone', 'SDA',
    'PDA', 'Handheld', 'Symbian',
    'WAP', 'Palm', 'Avantgo',
    'cHTML', 'BlackBerry', 'Opera Mini',
    'Nokia'
  );

  // Pr�fen der Browserkennung
  for ($i=0; $i<count($agents); $i++) {
    if(isset($_SERVER["HTTP_USER_AGENT"]) && strpos($_SERVER["HTTP_USER_AGENT"], $agents[$i]) !== false)
      return true;
  }

  return false;
}

?>