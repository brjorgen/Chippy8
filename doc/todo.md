
# Table of Contents

1.  [Basics!](#org573b20f)
2.  [Mid-project update](#org3b7ffc4)
3.  [Serious Stuff!](#org0124803)
4.  [End of project update](#org635c488)
5.  [Dissasembler](#org2d7ad20)
6.  [Misc questions](#org9dcb1e9)
    1.  [To separate or not to separate EMU/DISAS, <span class="underline">that</span> is the question (it's probably not that important)](#org5fee2e8)
    2.  [How should I emulate the audio?](#orgc074db7)
    3.  [Is implementing a tile system for the SDL window necessary or can i get away with some lazy ascii?](#org8c5d784)


<a id="org573b20f"></a>

# TODO Basics!

<table border="2" cellspacing="0" cellpadding="6" rules="groups" frame="hsides">


<colgroup>
<col  class="org-left" />

<col  class="org-left" />
</colgroup>
<thead>
<tr>
<th scope="col" class="org-left">Task</th>
<th scope="col" class="org-left">Done</th>
</tr>
</thead>

<tbody>
<tr>
<td class="org-left">Implement basic program structure</td>
<td class="org-left">x</td>
</tr>
</tbody>

<tbody>
<tr>
<td class="org-left">Makefiles</td>
<td class="org-left">x</td>
</tr>
</tbody>

<tbody>
<tr>
<td class="org-left">Impmement all instructions</td>
<td class="org-left">&#xa0;</td>
</tr>
</tbody>

<tbody>
<tr>
<td class="org-left">Unit test all instructions</td>
<td class="org-left">&#xa0;</td>
</tr>
</tbody>
</table>


<a id="org3b7ffc4"></a>

# TODO Mid-project update

<table border="2" cellspacing="0" cellpadding="6" rules="groups" frame="hsides">


<colgroup>
<col  class="org-left" />

<col  class="org-left" />
</colgroup>
<thead>
<tr>
<th scope="col" class="org-left">Task</th>
<th scope="col" class="org-left">Done</th>
</tr>
</thead>

<tbody>
<tr>
<td class="org-left">Review instruction code</td>
<td class="org-left">&#xa0;</td>
</tr>
</tbody>

<tbody>
<tr>
<td class="org-left">Refactor n.1</td>
<td class="org-left">&#xa0;</td>
</tr>
</tbody>
</table>


<a id="org0124803"></a>

# TODO Serious Stuff!

<table border="2" cellspacing="0" cellpadding="6" rules="groups" frame="hsides">


<colgroup>
<col  class="org-left" />

<col  class="org-left" />
</colgroup>
<thead>
<tr>
<th scope="col" class="org-left">Task</th>
<th scope="col" class="org-left">Done</th>
</tr>
</thead>

<tbody>
<tr>
<td class="org-left">handle keypresses</td>
<td class="org-left">&#xa0;</td>
</tr>
</tbody>

<tbody>
<tr>
<td class="org-left">implement clock stuff</td>
<td class="org-left">&#xa0;</td>
</tr>
</tbody>

<tbody>
<tr>
<td class="org-left">add sound + graphics + io with SDL</td>
<td class="org-left">&#xa0;</td>
</tr>
</tbody>
</table>


<a id="org635c488"></a>

# TODO End of project update

<table border="2" cellspacing="0" cellpadding="6" rules="groups" frame="hsides">


<colgroup>
<col  class="org-left" />

<col  class="org-left" />
</colgroup>
<thead>
<tr>
<th scope="col" class="org-left">Task</th>
<th scope="col" class="org-left">Done</th>
</tr>
</thead>

<tbody>
<tr>
<td class="org-left">Review instruction code</td>
<td class="org-left">&#xa0;</td>
</tr>
</tbody>

<tbody>
<tr>
<td class="org-left">Refactor n.1</td>
<td class="org-left">&#xa0;</td>
</tr>
</tbody>
</table>


<a id="org2d7ad20"></a>

# TODO Dissasembler

<table border="2" cellspacing="0" cellpadding="6" rules="groups" frame="hsides">


<colgroup>
<col  class="org-left" />

<col  class="org-left" />
</colgroup>
<thead>
<tr>
<th scope="col" class="org-left">Task</th>
<th scope="col" class="org-left">Done</th>
</tr>
</thead>

<tbody>
<tr>
<td class="org-left">Review mnemonics (come up with something not shit)</td>
<td class="org-left">&#xa0;</td>
</tr>


<tr>
<td class="org-left">Decide on instruction interface (u16 vs u8*)</td>
<td class="org-left">x</td>
</tr>


<tr>
<td class="org-left">Add another fptr indirection for two-part opcodes</td>
<td class="org-left">&#xa0;</td>
</tr>
</tbody>
</table>


<a id="org9dcb1e9"></a>

# TODO Misc questions


<a id="org5fee2e8"></a>

## To separate or not to separate EMU/DISAS, <span class="underline">that</span> is the question (it's probably not that important)

why not just make the dissasembler be an option from the main executable?
like ./chip8<sub>emu.bin</sub> &#x2013;disas or whatever?

I mean&#x2026; less voluminous emulator ig? It's not like that matters.


<a id="orgc074db7"></a>

## How should I emulate the audio?


<a id="org8c5d784"></a>

## Is implementing a tile system for the SDL window necessary or can i get away with some lazy ascii?

