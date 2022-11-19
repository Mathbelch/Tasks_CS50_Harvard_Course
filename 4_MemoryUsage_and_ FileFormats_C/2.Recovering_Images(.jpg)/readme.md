<h1>Recovering JPEGs images from a broken memory card</h1>
<p><b>TASK:</b> Create an algorithm - in C language - able to recover images from a file .jpg.</p>

<p><b>Context:</b><br>
<a href="https://www.paintshoppro.com/en/pages/jpeg-file/#:~:text=What%20is%20a%20JPEG%20File,images%20maintain%20reasonable%20image%20quality.">JPEG</a> stands for “Joint Photographic Experts Group”. It’s a standard image format for containing lossy and compressed image data. JPEGs files have <i>signature</i> that can be helpful to distinguish them from other files. The first three bytes from them are: 0xff 0xd8 0xff. The fourth byte however can be 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed  0xee or 0xef, but in all case it will be 1110.
<p>When recovering the images in a memory card we must not only check for the file extension to be correct, but also understand how the images are stored. Digital cameras generally use the FAT file system, where data is stored in blocks of 512 bytes, so an image will occupe how many blocks it is necessary to keep it, even if there is free spots in the block. </p>









