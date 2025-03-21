# PE Parser

This is a simple PE parser. The goal of this parser is to understand the PE (Portable Executable) file format.

I have parsed the following components:
- **DOS Header**
- **NT Header** (signature, file header, optional header)
- **Sections Header**
- **Imports Directory**
- **Base Relocation**

## Resources:
- [PE File Format Documentation](https://learn.microsoft.com/en-us/windows/win32/debug/pe-format#the-reloc-section-image-only)
- [A Comprehensive Guide on PE File Structure](https://0xrick.github.io/win-internals/pe1/) (A strong starting point for understanding PE files)
- [Sunshine2k: PE File Structure Tutorial](https://www.sunshine2k.de/reversing/tuts/tut_pe.htm)
