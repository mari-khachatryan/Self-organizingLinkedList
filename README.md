# SelfOrganizingLinkedList

The Self-Organizing Linked List (SOLL) is a C++ data structure that maintains a linked list of elements. It offers unique features for optimizing element retrieval and organization.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)

## Introduction

The Self-Organizing Linked List (SOLL) is a specialized data structure designed to optimize element access patterns. It reorganizes its elements based on how frequently they are accessed. This project provides an implementation of the SOLL in C++.

## Features

- **Self-Organizing**: The SOLL reorganizes elements based on access patterns to improve retrieval times.
- **Sorting**: Provides sorting capabilities for the elements in the list.
- **Merging**: Allows merging two SOLLs into a single one while maintaining order.
- **Splicing**: Enables efficient insertion of elements from another SOLL at a specified position.
- **Transpose**: Reorganizes elements by swapping an accessed element with its predecessor.
- **Insertion and Removal**: Easily add and remove elements from the list.
- **Memory Management**: Carefully manages memory allocation and deallocation for better performance.
- **Robust Error Handling**: Provides error handling mechanisms for out-of-bounds access and other exceptions.
- **Clear Error Messages**: Offers descriptive error messages for easier debugging.

## Getting Started

Follow these steps to get the SOLL project up and running on your local machine.

### Prerequisites

Before you begin, ensure you have met the following requirements:

- C++ development environment (e.g., g++)
- Git (for cloning the repository)

### Installation

1. Clone the SOLL repository:

   ```bash
   git clone https://github.com/NalbandyanElmira/SelfOrganizingLinkedList.git
   ```
   ```bash
   cd SelfOrganizingLinkedList
   ```
2. Build the project using your preferred C++ compiler:
   ```bash
   g++ main.cpp
   ```
   ```bash
   ./a.out
   ```

### Usage
Here's how you can use the SOLL in your C++ code:
<pre>
#include "soll.h"

int main() {
    // Create a Self-Organizing Linked List
    SOLL<int> list;

    // Add elements to the list
    list.push_back(42);
    list.push_front(10);

    // Sort the list
    list.sort();

    // Access elements efficiently
    int value = list.find(10);

    return 0;
}
</pre>
