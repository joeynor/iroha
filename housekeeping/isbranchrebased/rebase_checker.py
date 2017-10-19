from common import GithubCommon 
from context import GithubContext 

class RebaseChecker:
    def __init__(self, context):
        self.context = context
        self.common = GithubCommon(self.context)

    # data - parsed json, which we receive from github after
    # any PR update
    def after_pr_update(self, data):
        pr = data["pull_request"]
        prhead = pr["head"]
        prbase = pr["base"]
        prbase_sha = prbase["sha"]
        prhead_sha = prhead["sha"]

        base = self.common.get_latest_branch(self.context.base)
        base_sha = base["commit"]["sha"]

        # update status
        rebased = base_sha == prbase_sha
        ok = self.common.set_commit_status(prhead_sha, rebased)
        if ok:
            print("status updated: {}".format(rebased))
        else:
            print("status not updated")

    # data - parsed json, which we receive from github after
    # push to `base_name` branch
    # def after_base_push(self, data):


# with open("test/mock.open.json", "r") as f:
#     d = f.read()
#     j = json.loads(d)

#     ctx  = Context(token="9ba707b19a1c5708b87d3a56bc179785491f71e2",
#         owner="warchant",
#         repo="reed-solomon_syndrome_gf256",
#         base="master")

#     rb = RebaseChecker(ctx)
#     rb.after_pr_update(j)