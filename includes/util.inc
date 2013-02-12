<?php
    function get_getvar($name) {
        return isset($_GET[$name]) ? $_GET[$name] : NULL;
    }

    function get_postvar($name) {
        return isset($_POST[$name]) ? $_POST[$name] : NULL;
    }

    function get_cookievar($name) {
        return isset($_COOKIE[$name]) ? $_COOKIE[$name] : NULL;
    }

    function get_random_string($length) {
        $rangearr = array(
            array(ord('A'), ord('Z')),
            array(ord('a'), ord('z')),
            array(ord('0'), ord('9'))
        );
        $randstr = "";
        for ($i=0; $i < $length; $i++) {
            $cclass = mt_rand(0, 2);
            $randstr .= chr(mt_rand($rangearr[$cclass][0], $rangearr[$cclass][1]));
        }
        return $randstr;
    }
?>
