<ul>
    <?php

    $res = $mysqli->query("SELECT * FROM navigation ORDER BY id");
    if (!$res) {
        echo("Fehler bei Navl, ".$mysqli->error."");
    }

    while($row = $res->fetch_object())
    {
        if($page->title == $row->url)
        {
            echo '<li class="current">';
        }
        else
        {
            echo '<li>';
        }
        echo '<a href="?p='.$row->url.'">'.$row->title.'</a></li>';
    }
    ?>
</ul>