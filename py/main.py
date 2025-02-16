from database import Database
from bprint import bprint
import time
import os

db = Database()

def clear():
    if os.name == "posix":
        os.system("clear")
    else:
        os.system("cls")

def main():
    clear()
    bprint("To-do List —— Menu")
    print("")

    print("1. See To-do List")
    print("2. Add To-do")
    print("3. Exit")
    print("")

    action = input("$: ")
    action_formatted = action.replace(" ", "")

    if action_formatted == "1":
        see_list()
    elif action_formatted == "2":
        add_todo()
    elif action_formatted == "3":
        print("Goodbye!")
    else:
        print("Invalid action.")
        time.sleep(0.095)
        main()

def see_list():
    clear()
    bprint("To-do List —— List")
    print("")

    todo_list = db.get_list()
    if len(todo_list) < 1:
        print("No to-do yet! Add one!")
    else:
        for i, text in enumerate(todo_list, 1):
            print(f"{i}. {text}")
    print("")

    print("Done! Go back to menu? (y/n)")
    action = input("$: ")
    action_formatted = action.lower().replace(" ", "")

    if action_formatted == "y":
        main()
    elif action_formatted == "n":
        print("Goodbye")
    else:
        print("Invalid action.")
        time.sleep(0.095)
        main()

def add_todo():
    clear()
    bprint("To-do List —— Add")
    print("")

    print("Add your todo:")
    todo = input("$: ")
    db.add_todo(todo)
    print("")

    print("Done! Go back to menu? (y/n)")

    action = input("$: ")
    action_formatted = action.lower().replace(" ", "")

    if action_formatted == "y":
        main()
    elif action_formatted == "n":
        print("Goodbye")
    else:
        print("Invalid action.")
        time.sleep(0.095)
        main()

if __name__ == "__main__":
    main()
