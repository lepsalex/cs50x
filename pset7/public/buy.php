<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
      render("buy_form.php", ["title" => "Buy"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {

      // Validate Symbol
      if (empty($_POST["symbol"]))
      {
          apologize("You must provide a symbol.");
      }

      // Lookup symbol
      $symbol = lookup($_POST["symbol"]);

      if ($symbol !== FALSE)
      {
        $price = lookup($_POST["symbol"]);
      }
      else
      {
        apologize("Invalid symbol, please try again.");
      }

      // Validate Shares
      if (empty($_POST["shares"]))
      {
          apologize("You must provide a number of shares.");
      }
      else if (ctype_digit($_POST["shares"]) && $_POST["shares"] > 0 )
      {
          $qty = $_POST["shares"];
      } else {
          apologize("Number of shares must be a positive whole number.");
      }

      // Purchase stocks (if funds available)

      // Lookup user's cash balance
      $balances = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
      $cash = $balances[0]["cash"];

      // Calculate price of order
      $order = $qty * intval($price["price"]);

      // If we have more cash than the order total BUY BUY BUY!
      if ($cash >= $order)
      {
        // Convert Symbol to uppercase
        $symbol = strtoupper ($_POST["symbol"]);

        // Buy Stock
        $buy = query("INSERT INTO holdings (id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $symbol, $_POST["shares"]);

        // If successfully completed buy action
        if ($buy !== FALSE)
        {
          // Debit the user for the total amount of the sale
          $debit = query("UPDATE users SET cash = cash - $order WHERE id = ?", $_SESSION["id"]);

          // Store transaction to History
          $history = query("INSERT INTO history (id, transaction, symbol, shares, price) VALUES(?, ?, ?, ?, ?)", $_SESSION["id"], "BUY", $symbol, $_POST["shares"], $price["price"]);

          // redirect to portfolio
          redirect("/");
        }
      }
      else
      {
        apologize("Insufficient fund.");
      }
    }

?>
