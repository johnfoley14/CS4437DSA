import os
import requests
from bs4 import BeautifulSoup


# Function to download books from the Gutenberg top 100 list and store each as a plain text file
def download_gutenberg_books(folder_name="../books", limit=100):
    print("starting")
    # Create the "books" folder if it doesn't exist
    if not os.path.exists(folder_name):
        os.makedirs(folder_name)

    # URL of the top 100 books on Project Gutenberg
    top_books_url = 'https://www.gutenberg.org/browse/scores/top'
    response = requests.get(top_books_url)

    # Parse the webpage content using BeautifulSoup
    soup = BeautifulSoup(response.content, 'html.parser')

    # Find all links to books (they usually follow this pattern)
    book_links = []
    for a_tag in soup.select('ol li a'):
        print("Found a book on page")
        print(a_tag['href'])
        if a_tag['href'].startswith('/ebooks/'):
            book_links.append('https://www.gutenberg.org' + a_tag['href'])

        if len(book_links) >= limit:
            break

    # Download each book in plain text format and store directly in the "books" folder
    for book_link in book_links:
        book_page = requests.get(book_link)
        book_soup = BeautifulSoup(book_page.content, 'html.parser')

        # Try to find the plain text link
        txt_link = None
        for link in book_soup.find_all('a', href=True):
            if '.txt' in link['href']:
                txt_link = 'https://www.gutenberg.org' + link['href']
                break

        if txt_link:
            # Get book ID and name from the link
            book_id = book_link.split('/')[-1]
            book_title = book_soup.find('title').text.split(' by ')[0].strip()

            # Clean the book title to make it a valid file name (removing problematic characters)
            clean_book_title = ''.join(c for c in book_title if c.isalnum() or c in (' ', '_')).rstrip()

            # Download the plain text file
            txt_response = requests.get(txt_link)
            txt_file_path = os.path.join(folder_name, f"{clean_book_title}_{book_id}.txt")
            print(txt_file_path)

            # Save the text content to a file directly in the "books" folder
            try:
                with open(txt_file_path, 'wb') as f:
                    f.write(txt_response.content)
            except:
                print("Not Available")

            print(f"Downloaded: {clean_book_title}")


# Call the function
download_gutenberg_books()