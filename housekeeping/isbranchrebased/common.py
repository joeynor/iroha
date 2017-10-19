import requests
import json

class State:
    error = "error"
    pending = "pending"
    failure = "failure"
    success = "success"

class GithubCommon:
    def __init__(self, context):
        self.context = context

    def get_latest_branch(self, branch):
        r = requests.get("{api}/repos/{owner}/{repo}/branches/{branch}"
            .format(
                api=self.context.github_api, 
                owner=self.context.owner, 
                repo=self.context.repo,
                branch=branch))

        if r.ok:
            return json.loads(r.text)
        else:
            return None

    # sha: sha hash of commit
    # status_ok: True/False
    def set_commit_status(self, sha, status_ok):
        if status_ok:
            state = State.success
            desc = self.context.rebased
        else:
            state = State.error
            desc = self.context.not_rebased

        data = {
            "state": state,
            "target_url": self.context.target_url,
            "description": desc,
            "context": self.context.botname
        }

        r = requests.post("{api}/repos/{owner}/{repo}/statuses/{sha}"
            .format(
                api=self.context.github_api, 
                owner=self.context.owner, 
                repo=self.context.repo,
                sha=sha),
            json=data,
            headers={
                "Authorization": "token {token}".format(
                        token=self.context.token
                    )
            })

        return r.ok


# c = GithubCommon(Context(token="9ba707b19a1c5708b87d3a56bc179785491f71e2"))
# c.context.owner = "warchant"
# c.context.repo = "reed-solomon_syndrome_gf256"
# c.set_commit_status("a09e6c33245bfcbda8ddeb80265d8f07add5e349", True)
