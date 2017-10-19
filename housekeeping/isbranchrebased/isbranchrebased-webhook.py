#!/usr/bin/env python3

from context import GithubContext
from rebase_checker import RebaseChecker 
from flask import Flask, request

app = Flask(__name__)

ctx  = GithubContext(
	token="9ba707b19a1c5708b87d3a56bc179785491f71e2",
    owner="warchant",
    repo="reed-solomon_syndrome_gf256",
    base="master"
    )

checker = RebaseChecker(ctx)

@app.route("/", methods=["POST"])
def handle():
    data = request.get_json(silent=True)
    checker.after_pr_update(data)
    return "ok"

if __name__ == "__main__":
    app.run()
