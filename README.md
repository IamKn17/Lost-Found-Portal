# 🔍 Lost & Found Portal

> A C++ console application for managing lost and found items with intelligent matching algorithms


## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Compilation](#compilation)
  - [Running the Application](#running-the-application)
- [Usage](#usage)
- [How It Works](#how-it-works)
  - [Matching Algorithm](#matching-algorithm)
  - [Data Storage](#data-storage)
- [Project Structure](#project-structure)
- [Examples](#examples)
- [Future Enhancements](#future-enhancements)

---

## 🎯 Overview

The **Lost & Found Portal** is a command-line application designed to help users report and track lost or found items efficiently. The system uses an intelligent matching algorithm to suggest potential matches between lost and found items based on multiple criteria. 

### Key Capabilities

- 📝 Report lost items with detailed information
- 🔎 Report found items and browse matches
- ✅ Automatic phone number validation (10-digit format)
- 💾 Persistent storage using CSV files
- 🧠 Smart matching algorithm using similarity scoring
- 🏆 Top-K recommendations for best matches

---

## ✨ Features

| Feature | Description |
|---------|-------------|
| **Item Registration** | Add lost or found items with category, location, description, and contact details |
| **Input Validation** | Ensures data integrity with phone number validation and required field checks |
| **CSV Persistence** | All data is stored in `lost_items.csv` and `found_items.csv` for easy access |
| **Intelligent Matching** | Uses Jaccard similarity, category matching, and location matching algorithms |
| **Top-K Results** | Displays the most relevant matches for any lost item |
| **Cross-Platform** | Works seamlessly on Windows, Linux, and macOS |
| **Menu-Driven Interface** | User-friendly console navigation |

---

## 🚀 Getting Started

### Prerequisites

- A C++ compiler supporting **C++11** or later
  - **g++** (Linux/macOS)
  - **MinGW** (Windows)
  - **MSVC** (Visual Studio)
  - **Clang**

### Compilation

#### Using g++ (Recommended)

**Standard Version:**
```bash
g++ -std=c++11 lost_and_found.cpp -o lost_and_found
```

**Advanced Version (with Authentication):**
```bash
g++ -std=c++11 lost-and-found-2.cpp -o lost_and_found_v2
```

#### Using Visual Studio (Windows)

1. Open **Developer Command Prompt**
2. Navigate to the project directory
3. Run: 
```cmd
cl /EHsc /std:c++11 lost_and_found.cpp
```

### Running the Application

**Linux/macOS:**
```bash
./lost_and_found
# or for advanced version
./lost_and_found_v2
```

**Windows:**
```cmd
lost_and_found.exe
# or for advanced version
lost_and_found_v2.exe
```

---

## 💡 Usage

Upon launching the application, you'll see a menu-driven interface:

```
====================================
    LOST & FOUND PORTAL
====================================
1. Report Lost Item
2. Report Found Item
3. View All Lost Items
4. View All Found Items
5. Find Matches for Lost Item
6. Exit
====================================
Enter your choice: 
```

### Reporting a Lost Item

1. Select option `1`
2. Enter the following details:
   - **Name**: Your name
   - **Category**: Type of item (e.g., Electronics, Jewelry, Documents)
   - **Location**: Where you lost it
   - **Description**: Detailed description with keywords
   - **Phone Number**: 10-digit contact number

### Reporting a Found Item

1. Select option `2`
2. Enter similar details as above for the found item

### Finding Matches

1. Select option `5`
2. Choose a lost item from the list
3. View top matches ranked by similarity score

---

## 🧩 How It Works

### Matching Algorithm

The system employs a **multi-factor similarity scoring** approach:

#### 1️⃣ **Text Similarity (Jaccard Index)**
```
Jaccard Similarity = |A ∩ B| / |A ∪ B|
```
- Compares keywords in item descriptions
- Extracts common words between lost and found items
- Tokenizes descriptions and removes punctuation

**Example:**
- Lost: "Blue Sony wireless headphones"
- Found: "Sony blue headphones wireless"
- Common tokens:  {blue, sony, wireless, headphones}
- Jaccard Score: 4/4 = 1.0 (perfect match)

#### 2️⃣ **Category Matching**
- Adds bonus points if categories match exactly
- Weight: **+0.3** to similarity score
- Ensures items of the same type are prioritized

#### 3️⃣ **Location Matching**
- Adds bonus points if locations match
- Weight: **+0.2** to similarity score
- Helps find items in proximity

#### Final Score Calculation
```cpp
final_score = jaccard_similarity + category_bonus + location_bonus
```

**Scoring Range:** 0.0 (no match) to 1.5 (perfect match)

### Data Storage

#### CSV File Format

**lost_items.csv** / **found_items.csv**

```csv
name,category,location,description,phone_number
John Doe,Electronics,Library,Black iPhone 13,1234567890
Jane Smith,Jewelry,Cafeteria,Gold bracelet with engravings,9876543210
```

#### Compatible Software
- 📊 Microsoft Excel
- 📈 Google Sheets
- 📋 LibreOffice Calc
- 📝 Any text editor

#### Data Persistence
- CSV files are created automatically on first run
- Data persists across multiple sessions
- Easy to backup and transfer

---

## 📁 Project Structure

```
Lost-Found-Portal/
│
├── lost_and_found.cpp       # Standard version with CSV storage
├── lost-and-found-2.cpp     # Advanced version with authentication
├── lost_items. csv           # Generated:  Stores lost items data
├── found_items.csv          # Generated: Stores found items data
└── README.md                # This documentation
```

### Implementation Versions

#### 🔹 Standard Version (`lost_and_found.cpp`)
- Core lost & found functionality
- CSV-based persistence
- Top-K matching with similarity scores
- Phone number validation
- Menu-driven interface

#### 🔹 Advanced Version (`lost-and-found-2.cpp`)

**Additional Features:**

| Feature | Description |
|---------|-------------|
| 🔐 **User Authentication** | Secure signup and login system |
| 🧂 **Password Salting** | Each password gets a unique random salt for enhanced security |
| 🔒 **Strong Hashing** | Custom multi-round hashing algorithm (5000 iterations) |
| 🎯 **Hungarian Algorithm** | Optimal bipartite matching for lost-found pairs |
| ⚡ **Batch Processing** | Enter multiple items at once |

**Security Implementation:**

```cpp
// Password Security Flow
User Password → Add Random Salt → Strong Hash (5000 rounds) → Store Hash + Salt
```

**Hashing Details:**
- **Salt Generation**:  Random string generated using `rand()` and `clock()`
- **Hash Function**:  Dual-base polynomial rolling hash
  - Base 1: 91138233
  - Base 2: 97266353
  - 5000 iteration rounds for computational hardness
- **Storage**: Passwords are never stored in plain text
- **Verification**: Input password + stored salt → rehash → compare with stored hash

**Hungarian Algorithm:**
- Finds **optimal global matching** between lost and found items
- Minimizes total distance/cost across all matches
- Better than greedy Top-K for bulk matching scenarios

---

## 📖 Examples

### Example 1: Reporting a Lost Item

```
Enter your choice: 1

Enter Name: Alice Johnson
Enter Category: Electronics
Enter Location: Central Park
Enter Description: Blue wireless headphones Sony brand WH-1000XM4
Enter Phone Number: 5551234567

✓ Lost item reported successfully!
```

### Example 2: User Authentication (Advanced Version)

```
1. Signup
2. Login
Choice: 1

Choose username: alice123
Choose password: ********
Signup successful! 

Username: alice123
Password: ********
✓ Authentication successful! 

Number of LOST items: 2
```

**Behind the scenes:**
```
Password: mypass123
Salt Generated: 1847392_9384729
Combined:  mypass123#1847392_9384729
Hashed (5000 rounds): 847392847_938472938
Stored:  username=alice123, salt=1847392_9384729, hash=847392847_938472938
```

### Example 3: Finding Matches

```
Enter your choice: 5

Select a lost item:
1. Blue wireless headphones - Electronics - Central Park

Enter item number: 1

🔍 Searching for matches... 

Top 3 Matches: 
┌─────────────────────────────────────────────────────────┐
│ Match #1                                    Score: 0.92 │
├─────────────────────────────────────────────────────────┤
│ Name: Bob Smith                                         │
│ Category:  Electronics                                   │
│ Location: Central Park                                  │
│ Description:  Sony WH-1000XM4 blue headphones wireless   │
│ Contact: 5559876543                                     │
└─────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────┐
│ Match #2                                    Score: 0.65 │
├─────────────────────────────────────────────────────────┤
│ Name: Carol White                                       │
│ Category: Electronics                                   │
│ Location: Park Entrance                                 │
│ Description:  Wireless blue earbuds                      │
│ Contact: 5551122334                                     │
└─────────────────────────────────────────────────────────┘
```

### Example 4: CSV Output

After reporting items, the CSV file looks like: 

```csv
Alice Johnson,Electronics,Central Park,Blue wireless headphones Sony brand WH-1000XM4,5551234567
Bob Smith,Electronics,Library,Lost black wallet with cards,5559998877
```

---

## 🔮 Future Enhancements

### Planned Features

- [ ] **Web Interface**
  - Develop a browser-based version with React/Vue.js
  - RESTful API for mobile apps
  
- [ ] **Database Integration**
  - Replace CSV with SQLite/MySQL/PostgreSQL
  - Improved query performance and scalability
  - Use bcrypt or Argon2 for password hashing

- [ ] **Enhanced Security**
  - Implement industry-standard bcrypt/Argon2 hashing
  - Add 2FA (Two-Factor Authentication)
  - Session management with JWT tokens
  - Role-based access control (RBAC)

- [ ] **Machine Learning**
  - Implement NLP-based semantic similarity
  - Use Word2Vec or BERT embeddings
  - Deep learning for better matching

- [ ] **Image Recognition**
  - Upload and match items using computer vision
  - TensorFlow/PyTorch integration
  - Reverse image search functionality

- [ ] **Mobile Application**
  - iOS/Android native apps
  - Push notifications for matches
  - QR code generation for items

- [ ] **Admin Dashboard**
  - Moderation and analytics panel
  - User management
  - Statistics and reporting

- [ ] **Notifications**
  - Email/SMS alerts for new matches
  - Real-time updates via WebSockets

## 🔐 Security Notes

### Password Storage (Advanced Version)

The advanced version implements secure password storage using: 

1. **Salt Generation**
   - Unique random salt per user
   - Prevents rainbow table attacks
   - Generated using time-based randomization

2. **Multi-Round Hashing**
   - 5000 iteration rounds
   - Dual-base polynomial hashing
   - Computationally expensive for attackers
   - Prevents brute-force attacks

3. **No Plain Text Storage**
   - Passwords are never stored directly
   - Only salt + hash are persisted
   - Even developers cannot see user passwords
