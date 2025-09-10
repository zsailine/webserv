#!/usr/bin/env python3
import os
import sys
import cgi
import cgitb
import shutil
from datetime import datetime

cgitb.enable()

upload_dir = os.path.join(os.path.dirname(__file__), "uploads")
log_file = os.path.join(upload_dir, "data.txt")

if not os.path.isdir(upload_dir):
    os.makedirs(upload_dir, exist_ok=True)

form = cgi.FieldStorage()
message = ""

if os.environ.get("REQUEST_METHOD", "") == "POST":
    # DELETE
    if "delete_file" in form:
        file_to_delete = os.path.basename(form.getvalue("delete_file"))
        target_path = os.path.join(upload_dir, file_to_delete)
        if os.path.exists(target_path):
            os.remove(target_path)
            message = f"Fichier '{file_to_delete}' supprimé."
        else:
            message = f"Fichier '{file_to_delete}' introuvable."
    else:
        # Log POST data
        with open(log_file, "a", encoding="utf-8") as fh:
            time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            fh.write(f"==== POST @ {time} ====\n")
            for key in form.keys():
                if key != "avatar":
                    fh.write(f"{key} = {form.getvalue(key)}\n")
            fh.write("\n")

        if "avatar" in form:
            file_item = form["avatar"]
            if file_item.filename:
                file_name = os.path.basename(file_item.filename)
                target_path = os.path.join(upload_dir, file_name)
                with open(target_path, "wb") as f:
                    shutil.copyfileobj(file_item.file, f)

print("Content-Type: text/html", end="\r\n\r\n") 
print()

print(f"""<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.8/dist/css/bootstrap.min.css" rel="stylesheet">
    <title>Webserv Python CGI</title>
</head>
<body style="background: white; padding: 50px;">
    <h1 style="color: black">Hello webserv (Python CGI)!</h1>
""")

if message:
    print(f"<p><b>{message}</b></p>")

print("""
    <form class="d-block" method="POST" action="index.py" enctype="multipart/form-data">
        <div>
            <label for="name">Nom</label>
            <input class="form-control" type="text" name="name"/>
        </div>
        <div>
            <label for="age">Age</label>
            <input class="form-control" type="text" name="age"/>
        </div>
        <div>
            <label for="avatar">Upload un fichier</label>
        </div>
        <div>
            <input class="form-control" type="file" name="avatar"/>
        </div>
        <div>
            <button class="mt-3 btn btn-success" type="submit">Submit</button>
        </div>
    </form>

    <hr>

    <h2>Fichiers uploadés</h2>
    <ul>
""")

for file in os.listdir(upload_dir):
    if file in (".", "..", "data.txt"):
        continue
    print(f"""
        <li>{file} 
            <form method='POST' action='index.py' style='display:inline'>
                <input type='hidden' name='delete_file' value='{file}'/>
                <button class="mx-3 btn btn-danger" type='submit'>Delete</button>
            </form>
        </li>
    """)

print("""
    </ul>
</body>
</html>
""")
