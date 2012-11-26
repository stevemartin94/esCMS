<?php
    function get_getvar($name) {
        return isset($_GET[$name]) ? $_GET[$name] : NULL;
    }

    function get_cookievar($name) {
        return isset($_COOKIE[$name]) ? $_COOKIE[$name] : NULL;
    }
?>