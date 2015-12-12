<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
            <select class="form-control" name="symbol">
                <option disabled="" selected="" value="">Symbol</option>
                <?php foreach ($positions as $position): ?>
                    <option value="<?= $position["symbol"] ?>"><?= $position["symbol"] ?></option>
                <?php endforeach ?>
            </select>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Sell</button>
        </div>
    </fieldset>
</form>
