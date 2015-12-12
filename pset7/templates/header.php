<!DOCTYPE html>

<html>

    <head>

        <link href="/css/bootstrap.min.css" rel="stylesheet"/>
        <link href="/css/bootstrap-theme.min.css" rel="stylesheet"/>
        <link href="/css/styles.css" rel="stylesheet"/>

        <?php if (isset($title)): ?>
            <title>C$50 Finance: <?= htmlspecialchars($title) ?></title>
        <?php else: ?>
            <title>C$50 Finance</title>
        <?php endif ?>

        <script src="/js/jquery-1.11.1.min.js"></script>
        <script src="/js/bootstrap.min.js"></script>
        <script src="/js/scripts.js"></script>

    </head>

    <body>

        <div class="container">

            <div id="top">
                <div>
                  <a href="/"><img alt="C$50 Finance" src="/img/logo.gif"/></a>
                </div>
                <?php if (!stripos($_SERVER['REQUEST_URI'], 'login.php')) { ?>
                <ul class="nav nav-pills">
                    <li><a href="quote.php">Quote</a></li>
                    <li><a href="buy.php">Buy</a></li>
                    <li><a href="sell.php">Sell</a></li>
                    <li><a href="history.php">History</a></li>
                    <li><a href="passchange.php">Change Password</a></li>
                    <li><a href="logout.php"><strong>Log Out</strong></a></li>
                </ul>
                <?php } ?>
            </div>

            <div id="middle">
