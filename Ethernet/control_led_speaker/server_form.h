const char *HTML_SERVER_FORM = R""""(<!DOCTYPE html>
<html lang="en">

<head>
    <title>Arduino server form</title>
</head>

<body>
    <form action="" method="get">
        <input type="hidden" name="L" value="7" />
        <input type="submit" value="Toggle Red" />
    </form>
    <form action="" method="get">
        <input type="hidden" name="L" value="6" />
        <input type="submit" value="Toggle Green" />
    </form>
    <form action="" method="get">
        <input type="hidden" name="L" value="5" />
        <input type="submit" value="Toggle Blue" />
    </form>
    <form action="" method="get">
        <input type="range" name="S" min="0" max="1000" step="100" value="0" />
        <input type="submit" value="Set Frequency" />
    </form>
</body>

</html>)"""";