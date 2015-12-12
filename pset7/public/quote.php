<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("quote_form.php", ["title" => "Quote"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
      // validate submission
      if (empty($_POST["symbol"]))
      {
          apologize("You must provide a symbol.");
      }

      // Lookup symbol
      $symbol = lookup($_POST["symbol"]);

      if ($symbol !== FALSE)
      {
        render("quote.php",
          [
            "title" => "Quote: " . $_POST["symbol"],
            "symbol" => $symbol["symbol"],
            "name" => $symbol["name"],
            "price" => $symbol["price"],
          ]);
      }
      else
      {
        apologize("Invalid symbol, please try again.");
      }
    }

?>
