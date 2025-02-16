import json
import sys

class Database:
    def __init__(self):
        self.db = []
        self.seed = []

        try:
            with open("database.json", "r") as file:
                self.db = json.load(file)
        except (FileNotFoundError, json.JSONDecodeError):
            with open("database.json", "w") as file:
                json.dump(self.seed, file)
            self.db = self.seed
        except Exception as e:
            print(f"[-] Cannot init db! {e}")
            sys.exit(1)

    def get_list(self):
        return self.db

    def add_todo(self, todo):
        self.db.append(todo)
