#!/usr/bin/env python3

import ghooks
from ghooks import app

@ghooks.events('push')
def push_event(data):
    print("Push event triggered!")
    print(data)

if __name__ == "__main__":
    app.run()