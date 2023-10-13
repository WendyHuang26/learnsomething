import heapq

class Exchange:

    def __init__(self, initialBalance):
        """Initial Balance is the amount that each account should start with."""
        self.accounts = {} 
        self.bids = []  # priority queue for bids (buy orders)
        self.asks = []  # priority queue for asks (sell orders)
        self.initialBalance = initialBalance

    def add_trade(self, trade):
        """
        Adds a trade to the exchange (validation required)
        and returns a match if required.
        """
        account, order_type, price, quantity = trade

        # initialize account
        if account not in self.accounts:
            self.accounts[account] = self.initialBalance

        # validate
        if not self.is_valid_trade(trade):
            return None

        # if buy, add to bids
        if order_type == "buy":
            heapq.heappush(self.bids, (-price, quantity, account))
        else: #else add to asks.
            heapq.heappush(self.asks, (price, quantity, account))

        # check for matches
        match = self._find_match()
        return match

    def is_valid_trade(self, trade):
        """Validates the trade - checks if the account has enough balance."""
        account, order_type, price, quantity = trade

        if order_type == "buy" and self.accounts[account] < price * quantity:
            return False
        
        return True

    def _find_match(self):
        """Finds a match between bids and asks."""
        while self.bids and self.asks:

            bid_price, _, bid_account = -self.bids[0][0], self.bids[0][1], self.bids[0][2]
            ask_price, _, ask_account = self.asks[0]

            # match
            if bid_price >= ask_price:
                bid = heapq.heappop(self.bids)
                ask = heapq.heappop(self.asks)

                matched_quantity = min(bid[1], ask[1])

                # update
                self.accounts[bid_account] -= matched_quantity * bid_price
                self.accounts[ask_account] += matched_quantity * bid_price

                # push remaining
                if bid[1] > matched_quantity:
                    heapq.heappush(self.bids, (bid[0], bid[1] - matched_quantity, bid_account))
                elif ask[1] > matched_quantity:
                    heapq.heappush(self.asks, (ask[0], ask[1] - matched_quantity, ask_account))

                return (bid_account, "bought", matched_quantity, ask_account, "sold", matched_quantity)
            else:
                break
        return None

# testing
exchange = Exchange(1000)
print(exchange.add_trade(("AccountA", "buy", 100, 5)))  # no match, returns None
print(exchange.add_trade(("AccountB", "sell", 90, 3)))  # match
