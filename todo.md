
# Table of Contents

1.  [Basics!](#org932b95e)
2.  [Mid-project update](#orgee77841)
3.  [Serious Stuff!](#org696083b)
4.  [Dissasembler](#orge596775)
5.  [Misc questions](#org7e4176a)
    1.  [To separate or not to separate EMU/DISAS, <span class="underline">that</span> is the question (it's probably not that important)](#orgdc9913b)
    2.  [How should I emulate the audio?](#org9d95cb6)
    3.  [Is implementing a tile system for the SDL window necessary or can i get away with some lazy ascii?](#org5457733)


<a id="org932b95e"></a>

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


<a id="orgee77841"></a>

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


<a id="org696083b"></a>

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
<td class="org-left">Implement clock stuff</td>
<td class="org-left">&#xa0;</td>
</tr>
</tbody>

<tbody>
<tr>
<td class="org-left">Add sound + graphics + IO with SDL</td>
<td class="org-left">&#xa0;</td>
</tr>
</tbody>
</table>


<a id="orge596775"></a>

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


<a id="org7e4176a"></a>

# TODO Misc questions


<a id="orgdc9913b"></a>

## To separate or not to separate EMU/DISAS, <span class="underline">that</span> is the question (it's probably not that important)

why not just make the dissasembler be an option from the main executable?
like ./chip8<sub>emu.bin</sub> &#x2013;disas or whatever?

I mean&#x2026; less voluminous emulator ig? It's not like that matters.


<a id="org9d95cb6"></a>

## How should I emulate the audio?


<a id="org5457733"></a>

## Is implementing a tile system for the SDL window necessary or can i get away with some lazy ascii?

