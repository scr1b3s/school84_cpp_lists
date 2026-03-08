#!/usr/bin/env python3
"""
Convert PDF to Markdown (plain text extraction)
Keeps original structure and formatting as much as possible

Usage: python3 pdf_to_md.py <pdf_path>
Example: python3 pdf_to_md.py resources/cpp07/en.subject.pdf
"""

import subprocess
import sys
import os
from pathlib import Path


def pdf_to_text(pdf_path):
    """Extract text from PDF using pdftotext"""
    try:
        result = subprocess.run(
            ['pdftotext', pdf_path, '-'],
            capture_output=True,
            text=True,
            check=True
        )
        return result.stdout
    except subprocess.CalledProcessError as e:
        print(f"Error extracting PDF: {e}", file=sys.stderr)
        return None
    except FileNotFoundError:
        print(
            "Error: pdftotext not found. Install with: sudo apt-get install poppler-utils",
            file=sys.stderr
        )
        return None


def text_to_markdown(text):
    """Convert plain text to readable Markdown"""
    lines = text.split('\n')
    md_lines = []

    for line in lines:
        # Preserve empty lines for readability
        if not line.strip():
            md_lines.append('')
        # Convert lines that look like headers (all caps, reasonable length)
        elif line.isupper() and len(line.strip()) > 10 and len(line.strip()) < 100:
            md_lines.append(f"# {line.strip()}")
        else:
            md_lines.append(line)

    return '\n'.join(md_lines)


def create_md_from_pdf(pdf_path):
    """Main function: PDF → MD conversion"""

    # Validate PDF exists
    if not os.path.exists(pdf_path):
        print(f"Error: PDF file not found: {pdf_path}", file=sys.stderr)
        return False

    # Generate output path (same name, .md extension)
    pdf_path_obj = Path(pdf_path)
    md_path = pdf_path_obj.with_suffix('.md')

    # Check if .md already exists
    if md_path.exists():
        print(f"Info: {md_path} already exists. Skipping.")
        return True

    # Extract text from PDF
    print(f"Converting {pdf_path} to {md_path}...")
    text = pdf_to_text(pdf_path)

    if text is None:
        return False

    # Convert to Markdown
    markdown_content = text_to_markdown(text)

    # Write to file
    try:
        with open(md_path, 'w', encoding='utf-8') as f:
            f.write(markdown_content)
        print(f"✓ Successfully created: {md_path}")
        return True
    except IOError as e:
        print(f"Error writing file: {e}", file=sys.stderr)
        return False


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 pdf_to_md.py <pdf_path>")
        print("Example: python3 pdf_to_md.py resources/cpp07/en.subject.pdf")
        sys.exit(1)

    pdf_path = sys.argv[1]
    success = create_md_from_pdf(pdf_path)
    sys.exit(0 if success else 1)
