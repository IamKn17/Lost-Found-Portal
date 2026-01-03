# Lost & Found – C++ Console Application

## 1. Overview

This is a C++ console application that simulates a **Lost & Found system**. It allows users to:

- Report lost items (category, location, description, contact number)
- Report found items with similar details
- Validate phone numbers to ensure correctness (10 digits)
- Store items in CSV files (`lost_items.csv`, `found_items.csv`) for persistence

The program also includes a **matching algorithm** that computes similarity between lost and found items using:

- **Text similarity** (Jaccard similarity of description keywords)
- **Category match**
- **Location match**

The application then displays the **Top-K most similar matches** for a given lost item.

---

## 2. How to Compile & Run

This program is written in standard C++ and works on Windows, Linux, and macOS.

### ▶️ Using g++ (Recommended)

```bash
g++ -std=c++11 lost_and_found.cpp -o lost_and_found
./lost_and_found
For Version 2:

bash
Copy code
g++ -std=c++11 lost_and_found_v2.cpp -o lost_and_found_v2
./lost_and_found_v2
On Windows:

bash
Copy code
lost_and_found.exe
lost_and_found_v2.exe
3. Project Structure
File	Description
lost_and_found.cpp	Base implementation
lost_and_found_v2.cpp	Updated/enhanced version

Both versions implement the same Lost & Found functionality but differ in code structure and enhancements.

4. Features
Add lost item entry

Add found item entry

Input validation

Save data to CSV

Read stored data back

Keyword-based matching algorithm

Display top-K possible matches

Simple console menu interface

5. Matching Algorithm (Summary)
The application compares every lost item with every found item.

A similarity score is calculated using:

Jaccard similarity on descriptions

Bonus points for same category

Bonus points for same location

Results are sorted and best matches are displayed.

6. CSV File Format
The application writes data into:

lost_items.csv

found_items.csv

Each row is stored as:

pgsql
Copy code
name, category, location, description, phone_number
CSV files can be opened in:

Excel

Google Sheets

LibreOffice

Any text editor

7. Differences Between Versions
Version 1 – lost_and_found.cpp
Core features implemented

Basic menu-driven interface

Fundamental matching logic

Version 2 – lost_and_found_v2.cpp
Cleaner modular code

Improved validation

Better user interaction

Enhanced matching/scoring behavior

Additional error handling

8. Future Enhancements
Potential improvements:

GUI or Web version

Online database instead of CSV

Machine-learning based similarity search

Image upload and visual matching

Admin moderation panel

9. License
This project is intended for educational and academic use.
You may modify or distribute it with appropriate credit.

