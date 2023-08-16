
function opt_STACK_CMP(i: integer): Boolean;
var p: integer;
begin

    Result := true;

// -----------------------------------------------------------------------------
// ===				      CMP.
// -----------------------------------------------------------------------------


    if lab_a(i) and										//@					; 0
       sty_stack(i+1) and									// sty :STACKORIGIN+2,x			; 1
       lda_stack(i+2) and									// lda :STACKORIGIN+1,x			; 2
       and_ora_eor_stack(i+3) then								// and|ora|eor :STACKORIGIN+2,x		; 3
     if (copy(listing[i+1], 6, 256) = copy(listing[i+3], 6, 256)) and
        (copy(listing[i+1], 6, 256) <> copy(listing[i+2], 6, 256)) then
     begin
       listing[i+1] := #9'tya';
       listing[i+2] := copy(listing[i+3], 1, 5) + copy(listing[i+2], 6, 256);
       listing[i+3] := '';

       exit(false);
     end;


    if lab_a(i) and										//@					; 0
       sty_stack(i+1) and									// sty :STACKORIGIN			; 1
       lda_stack(i+2) then									// lda :STACKORIGIN			; 2
    if copy(listing[i+1], 6, 256) = copy(listing[i+2], 6, 256) then
     begin
       listing[i+1] := #9'tya';
       listing[i+2] := '';

       exit(false);
     end;


    if lab_a(i) and										//@					; 0
       tya(i+1) and										// tya					; 1
       (listing[i+2] = #9'sta :STACKORIGIN,x') and						// sta :STACKORIGIN,x			; 2
       dex(i+3) then										// dex					; 3
     begin
       listing[i+2] := #9'sty :STACKORIGIN+1,x';

       listing[i+1] := #9'dex';

       listing[i+3] := '';

       exit(false);
     end;


    if lab_a(i) and										//@					; 0
       (listing[i+1] = #9'sty :STACKORIGIN-1,x') and						// sty :STACKORIGIN-1,x			; 1
       dex(i+2) then										// dex					; 2
     begin
       listing[i+2] := #9'sty :STACKORIGIN,x';

       listing[i+1] := #9'dex';

       exit(false);
     end;


    if lab_a(i) and										//@					; 0
       (listing[i+1] = #9'sty :STACKORIGIN,x') and						// sty :STACKORIGIN,x			; 1
       dex(i+2) then										// dex					; 2
     begin
       listing[i+2] := #9'sty :STACKORIGIN+1,x';

       listing[i+1] := #9'dex';

       exit(false);
     end;


    if lab_a(i) and										//@					; 0
       (listing[i+1] = #9'sty :STACKORIGIN+1,x') and						// sty :STACKORIGIN+1,x			; 1
       dex(i+2) then										// dex					; 2
     begin
       listing[i+2] := #9'sty :STACKORIGIN+2,x';

       listing[i+1] := #9'dex';

       exit(false);
     end;



    if ldy_1(i) and										// ldy #1    				; 0

       lab_a(i+6) and										//@					; 6

       lab_a(i+10) and										//@					; 10
       sty_stack(i+11) and									// sty :STACKORIGIN			; 11
       dex(i+12) then										// dex					; 12
     begin

	    if (listing[i+11] = #9'sty :STACKORIGIN-1,x') then				// sty :STACKORIGIN-1,x		; 11
	     begin
	       listing[i+12] := #9'sty :STACKORIGIN,x';

	       listing[i+11] := #9'dex';

	       exit(false);
	     end;


	    if (listing[i+11] = #9'sty :STACKORIGIN,x') then				// sty :STACKORIGIN,x		; 11
	     begin
	       listing[i+12] := #9'sty :STACKORIGIN+1,x';

	       listing[i+11] := #9'dex';

	       exit(false);
	     end;


	    if (listing[i+11] = #9'sty :STACKORIGIN+1,x') then				// sty :STACKORIGIN+1,x		; 11
	     begin
	       listing[i+12] := #9'sty :STACKORIGIN+2,x';

	       listing[i+11] := #9'dex';

	       exit(false);
	     end;

     end;



    if (listing[i+1] = #9'.LOCAL') and								// .LOCAL				; 1

       lab_a(i+20) and										//@					; 20
       sty_stack(i+21) and									// sty :STACKORIGIN			; 21
       dex(i+22) then										// dex					; 22
     begin

	    if (listing[i+21] = #9'sty :STACKORIGIN-1,x') then				// sty :STACKORIGIN-1,x		; 21
	     begin
	       listing[i+22] := #9'sty :STACKORIGIN,x';

	       listing[i+21] := #9'dex';

	       exit(false);
	     end;


	    if (listing[i+21] = #9'sty :STACKORIGIN,x') then				// sty :STACKORIGIN,x		; 21
	     begin
	       listing[i+22] := #9'sty :STACKORIGIN+1,x';

	       listing[i+21] := #9'dex';

	       exit(false);
	     end;


	    if (listing[i+21] = #9'sty :STACKORIGIN+1,x') then				// sty :STACKORIGIN+1,x		; 21
	     begin
	       listing[i+22] := #9'sty :STACKORIGIN+2,x';

	       listing[i+21] := #9'dex';

	       exit(false);
	     end;

     end;



    if ldy_1(i) and										// ldy #1				; 0
       lda(i+1) and (lda_stack(i+1) = false) and						// lda A				; 1
       cmp(i+2) and (cmp_stack(i+2) = false) and						// cmp B				; 2
       SKIP(i+3) and										// SKIP					; 3
       dey(i+4) and										// dey					; 4
       lab_a(i+5) and										//@					; 5
       dex(i+6) then										// dex					; 6
     begin
       listing[i+6] := listing[i+5];
       listing[i+5] := listing[i+4];
       listing[i+4] := listing[i+3];
       listing[i+3] := listing[i+2];
       listing[i+2] := listing[i+1];
       listing[i+1] := listing[i];

       listing[i] := #9'dex';

       exit(false);
     end;


    if ldy_1(i) and										// ldy #1				; 0
       (listing[i+1] = #9'lda :STACKORIGIN-1,x') and						// lda :STACKORIGIN-1,x			; 1
       (listing[i+2] = #9'cmp :STACKORIGIN,x') and						// cmp :STACKORIGIN,x			; 2
       SKIP(i+3) and										// SKIP					; 3
       dey(i+4) and										// dey					; 4
       lab_a(i+5) and										//@					; 5
       dex(i+6) then										// dex					; 6
     begin
       listing[i+6] := listing[i+5];
       listing[i+5] := listing[i+4];
       listing[i+4] := listing[i+3];
       listing[i+3] := #9'cmp :STACKORIGIN+1,x';
       listing[i+2] := #9'lda :STACKORIGIN,x';
       listing[i+1] := listing[i];

       listing[i] := #9'dex';

       exit(false);
     end;


    if ldy_1(i) and										// ldy #1				; 0
       (listing[i+1] = #9'lda :STACKORIGIN,x') and						// lda :STACKORIGIN,x			; 1
       (listing[i+2] = #9'cmp :STACKORIGIN+1,x') and						// cmp :STACKORIGIN+1,x			; 2
       SKIP(i+3) and										// SKIP					; 3
       dey(i+4) and										// dey					; 4
       lab_a(i+5) and										//@					; 5
       dex(i+6) then										// dex					; 6
     begin
       listing[i+6] := listing[i+5];
       listing[i+5] := listing[i+4];
       listing[i+4] := listing[i+3];
       listing[i+3] := #9'cmp :STACKORIGIN+2,x';
       listing[i+2] := #9'lda :STACKORIGIN+1,x';
       listing[i+1] := listing[i];

       listing[i] := #9'dex';

       exit(false);
     end;


    if ldy_1(i) and										// ldy #1				; 0
       lda(i+1) and (lda_stack(i+1) = false) and						// lda					; 1
       (listing[i+2] = #9'cmp :STACKORIGIN-1,x') and						// cmp :STACKORIGIN-1,x			; 2
       SKIP(i+3) and										// SKIP					; 3
       dey(i+4) and										// dey					; 4
       lab_a(i+5) and										//@					; 5
       dex(i+6) then										// dex					; 6
     begin
       listing[i+6] := listing[i+5];
       listing[i+5] := listing[i+4];
       listing[i+4] := listing[i+3];
       listing[i+3] := #9'cmp :STACKORIGIN,x';
       listing[i+2] := listing[i+1];
       listing[i+1] := listing[i];

       listing[i] := #9'dex';

       exit(false);
     end;


    if ldy_1(i) and										// ldy #1				; 0
       lda(i+1) and (lda_stack(i+1) = false) and						// lda					; 1
       (listing[i+2] = #9'cmp :STACKORIGIN,x') and						// cmp :STACKORIGIN,x			; 2
       SKIP(i+3) and										// SKIP					; 3
       dey(i+4) and										// dey					; 4
       lab_a(i+5) and										//@					; 5
       dex(i+6) then										// dex					; 6
     begin
       listing[i+6] := listing[i+5];
       listing[i+5] := listing[i+4];
       listing[i+4] := listing[i+3];
       listing[i+3] := #9'cmp :STACKORIGIN+1,x';
       listing[i+2] := listing[i+1];
       listing[i+1] := listing[i];

       listing[i] := #9'dex';

       exit(false);
     end;


    if ldy_1(i) and										// ldy #1				; 0
       (listing[i+1] = #9'lda :STACKORIGIN-1,x') and						// lda :STACKORIGIN-1,x			; 1
       cmp(i+2) and (cmp_stack(i+2) = false) and						// cmp					; 2
       SKIP(i+3) and										// SKIP					; 3
       dey(i+4) and										// dey					; 4
       lab_a(i+5) and										//@					; 5
       dex(i+6) then										// dex					; 6
     begin
       listing[i+6] := listing[i+5];
       listing[i+5] := listing[i+4];
       listing[i+4] := listing[i+3];
       listing[i+3] := listing[i+2];
       listing[i+2] := #9'lda :STACKORIGIN,x';
       listing[i+1] := listing[i];

       listing[i] := #9'dex';

       exit(false);
     end;


    if ldy_1(i) and										// ldy #1				; 0
       (listing[i+1] = #9'lda :STACKORIGIN,x') and						// lda :STACKORIGIN,x			; 1
       cmp(i+2) and (cmp_stack(i+2) = false) and						// cmp					; 2
       SKIP(i+3) and										// SKIP					; 3
       dey(i+4) and										// dey					; 4
       lab_a(i+5) and										//@					; 5
       dex(i+6) then										// dex					; 6
     begin
       listing[i+6] := listing[i+5];
       listing[i+5] := listing[i+4];
       listing[i+4] := listing[i+3];
       listing[i+3] := listing[i+2];
       listing[i+2] := #9'lda :STACKORIGIN+1,x';
       listing[i+1] := listing[i];

       listing[i] := #9'dex';

       exit(false);
     end;


    if ldy_1(i) and										// ldy #1				; 0
       (listing[i+1] = #9'lda :STACKORIGIN+1,x') and						// lda :STACKORIGIN+1,x			; 1
       cmp(i+2) and (cmp_stack(i+2) = false) and						// cmp					; 2
       SKIP(i+3) and										// SKIP					; 3
       dey(i+4) and										// dey					; 4
       lab_a(i+5) and										//@					; 5
       dex(i+6) then										// dex					; 6
     begin
       listing[i+6] := listing[i+5];
       listing[i+5] := listing[i+4];
       listing[i+4] := listing[i+3];
       listing[i+3] := listing[i+2];
       listing[i+2] := #9'lda :STACKORIGIN+2,x';
       listing[i+1] := listing[i];

       listing[i] := #9'dex';

       exit(false);
     end;




    if ldy_1(i) and										// ldy #1				; 0
       (listing[i+1] = #9'lda :STACKORIGIN-1,x') and						// lda :STACKORIGIN-1,x			; 1
       cmp(i+2) and (cmp_stack(i+2) = false) and						// cmp					; 2
       SKIP(i+3) and										// SKIP					; 3
       SKIP(i+4) and										// SKIP					; 4
       dey(i+5) and										// dey					; 5
       lab_a(i+6) and										//@					; 6
       dex(i+7) then										// dex					; 7
     begin
       listing[i+7] := listing[i+6];
       listing[i+6] := listing[i+5];
       listing[i+5] := listing[i+4];
       listing[i+4] := listing[i+3];
       listing[i+3] := listing[i+2];
       listing[i+2] := #9'lda :STACKORIGIN,x';
       listing[i+1] := listing[i];

       listing[i] := #9'dex';

       exit(false);
     end;


    if ldy_1(i) and										// ldy #1				; 0
       (listing[i+1] = #9'lda :STACKORIGIN,x') and						// lda :STACKORIGIN,x			; 1
       cmp(i+2) and (cmp_stack(i+2) = false) and						// cmp					; 2
       SKIP(i+3) and										// SKIP					; 3
       SKIP(i+4) and										// SKIP					; 4
       dey(i+5) and										// dey					; 5
       lab_a(i+6) and										//@					; 6
       dex(i+7) then										// dex					; 7
     begin
       listing[i+7] := listing[i+6];
       listing[i+6] := listing[i+5];
       listing[i+5] := listing[i+4];
       listing[i+4] := listing[i+3];
       listing[i+3] := listing[i+2];
       listing[i+2] := #9'lda :STACKORIGIN+1,x';
       listing[i+1] := listing[i];

       listing[i] := #9'dex';

       exit(false);
     end;


    if ldy_1(i) and										// ldy #1				; 0
       (listing[i+1] = #9'lda :STACKORIGIN+1,x') and						// lda :STACKORIGIN+1,x			; 1
       cmp(i+2) and (cmp_stack(i+2) = false) and						// cmp					; 2
       SKIP(i+3) and										// SKIP					; 3
       SKIP(i+4) and										// SKIP					; 4
       dey(i+5) and										// dey					; 5
       lab_a(i+6) and										//@					; 6
       dex(i+7) then										// dex					; 7
     begin
       listing[i+7] := listing[i+6];
       listing[i+6] := listing[i+5];
       listing[i+5] := listing[i+4];
       listing[i+4] := listing[i+3];
       listing[i+3] := listing[i+2];
       listing[i+2] := #9'lda :STACKORIGIN+2,x';
       listing[i+1] := listing[i];

       listing[i] := #9'dex';

       exit(false);
     end;


    if lda(i) and (lda_stack(i) = false) and							// lda					; 0
       ldy_1(i+1) and										// ldy #1				; 1
       and_ora_eor(i+2) and (and_ora_eor_stack(i+2) = false) and				// and|ora|eor				; 2
       cmp(i+3) and (cmp_stack(i+3) = false) and						// cmp					; 3
       SKIP(i+4) and										// SKIP					; 4
       dey(i+5) and										// dey					; 5
       lab_a(i+6) and										//@					; 6
       dex(i+7) then										// dex					; 7
     begin
       listing[i+7] := listing[i+6];
       listing[i+6] := listing[i+5];
       listing[i+5] := listing[i+4];
       listing[i+4] := listing[i+3];
       listing[i+3] := listing[i+2];
       listing[i+2] := listing[i+1];
       listing[i+1] := listing[i];

       listing[i] := #9'dex';

       exit(false);
     end;




    if ldy_1(i) and										// ldy #1				; 0
       (listing[i+1] = #9'lda :STACKORIGIN-1+STACKWIDTH,x') and					// lda :STACKORIGIN-1+STACKWIDTH,x	; 1
       cmp(i+2) and (cmp_stack(i+2) = false) and						// cmp					; 2
       bne(i+3) and										// bne @+				; 3
       (listing[i+4] = #9'lda :STACKORIGIN-1,x') and						// lda :STACKORIGIN-1,x			; 4
       cmp(i+5) and (cmp_stack(i+5) = false) and						// cmp					; 5
       lab_a(i+6) and										//@					; 6
       SKIP(i+7) and										// SKIP					; 7
       dey(i+8) and										// dey					; 8
       lab_a(i+9) and										//@					; 9
       dex(i+10) then										// dex					; 10
     begin
	listing[i+10] := listing[i+9];
	listing[i+9] := listing[i+8];
	listing[i+8] := listing[i+7];
	listing[i+7] := listing[i+6];
	listing[i+6] := listing[i+5];
	listing[i+5] := #9'lda :STACKORIGIN,x';
	listing[i+4] := listing[i+3];
	listing[i+3] := listing[i+2];
	listing[i+2] := #9'lda :STACKORIGIN+STACKWIDTH,x';
	listing[i+1] := listing[i];

	listing[i] := #9'dex';

        exit(false);
     end;


    if ldy_1(i) and										// ldy #1				; 0
       (listing[i+1] = #9'lda :STACKORIGIN+STACKWIDTH,x') and					// lda :STACKORIGIN+STACKWIDTH,x	; 1
       cmp(i+2) and (cmp_stack(i+2) = false) and						// cmp					; 2
       bne(i+3) and										// bne @+				; 3
       (listing[i+4] = #9'lda :STACKORIGIN,x') and						// lda :STACKORIGIN,x			; 4
       cmp(i+5) and (cmp_stack(i+5) = false) and						// cmp					; 5
       lab_a(i+6) and										//@					; 6
       SKIP(i+7) and										// SKIP					; 7
       dey(i+8) and										// dey					; 8
       lab_a(i+9) and										//@					; 9
       dex(i+10) then										// dex					; 10
     begin
	listing[i+10] := listing[i+9];
	listing[i+9] := listing[i+8];
	listing[i+8] := listing[i+7];
	listing[i+7] := listing[i+6];
	listing[i+6] := listing[i+5];
	listing[i+5] := #9'lda :STACKORIGIN+1,x';
	listing[i+4] := listing[i+3];
	listing[i+3] := listing[i+2];
	listing[i+2] := #9'lda :STACKORIGIN+1+STACKWIDTH,x';
	listing[i+1] := listing[i];

	listing[i] := #9'dex';

        exit(false);
     end;


    if ldy_1(i) and										// ldy #1				; 0
       (listing[i+1] = #9'lda :STACKORIGIN+1+STACKWIDTH,x') and					// lda :STACKORIGIN+1+STACKWIDTH,x	; 1
       cmp(i+2) and (cmp_stack(i+2) = false) and						// cmp					; 2
       bne(i+3) and										// bne @+				; 3
       (listing[i+4] = #9'lda :STACKORIGIN+1,x') and						// lda :STACKORIGIN+1,x			; 4
       cmp(i+5) and (cmp_stack(i+5) = false) and						// cmp					; 5
       lab_a(i+6) and										//@					; 6
       SKIP(i+7) and										// SKIP					; 7
       dey(i+8) and										// dey					; 8
       lab_a(i+9) and										//@					; 9
       dex(i+10) then										// dex					; 10
     begin
	listing[i+10] := listing[i+9];
	listing[i+9] := listing[i+8];
	listing[i+8] := listing[i+7];
	listing[i+7] := listing[i+6];
	listing[i+6] := listing[i+5];
	listing[i+5] := #9'lda :STACKORIGIN+2,x';
	listing[i+4] := listing[i+3];
	listing[i+3] := listing[i+2];
	listing[i+2] := #9'lda :STACKORIGIN+2+STACKWIDTH,x';
	listing[i+1] := listing[i];

	listing[i] := #9'dex';

        exit(false);
     end;



// -----------------------------------------------------------------------------
//	CARDINAL
// -----------------------------------------------------------------------------

    if //inx(i) and										// inx					; 0
       mva(i+1) and 										// mva .. :STACKORIGIN,x		; 1
       mva(i+2) and										// mva .. :STACKORIGIN+STACKWIDTH,x	; 2
       mva(i+3) and										// mva .. :STACKORIGIN+STACKWIDTH*2,x	; 3
       mva(i+4) and										// mva .. :STACKORIGIN+STACKWIDTH*3,x	; 4
       inx(i+5) and										// inx					; 5
       mva(i+6) and 										// mva .. :STACKORIGIN,x		; 6
       mva(i+7) and										// mva .. :STACKORIGIN+STACKWIDTH,x	; 7
       mva(i+8) and										// mva .. :STACKORIGIN+STACKWIDTH*2,x	; 8
       mva(i+9) and										// mva .. :STACKORIGIN+STACKWIDTH*3,x	; 9
       ldy_1(i+10) and										// ldy #1				; 10
       (listing[i+11] = #9'lda :STACKORIGIN-1+STACKWIDTH*3,x') and				// lda :STACKORIGIN-1+STACKWIDTH*3,x	; 11
       (listing[i+12] = #9'cmp :STACKORIGIN+STACKWIDTH*3,x') and				// cmp :STACKORIGIN+STACKWIDTH*3,x	; 12
       bne(i+13) and										// bne @+				; 13
       (listing[i+14] = #9'lda :STACKORIGIN-1+STACKWIDTH*2,x') and				// lda :STACKORIGIN-1+STACKWIDTH*2,x	; 14
       (listing[i+15] = #9'cmp :STACKORIGIN+STACKWIDTH*2,x') and				// cmp :STACKORIGIN+STACKWIDTH*2,x	; 15
       bne(i+16) and										// bne @+				; 16
       (listing[i+17] = #9'lda :STACKORIGIN-1+STACKWIDTH,x') and				// lda :STACKORIGIN-1+STACKWIDTH,x	; 17
       (listing[i+18] = #9'cmp :STACKORIGIN+STACKWIDTH,x') and					// cmp :STACKORIGIN+STACKWIDTH,x	; 18
       bne(i+19) and										// bne @+				; 19
       (listing[i+20] = #9'lda :STACKORIGIN-1,x') and						// lda :STACKORIGIN-1,x			; 20
       (listing[i+21] = #9'cmp :STACKORIGIN,x') then						// cmp :STACKORIGIN,x			; 21
     if (pos(':STACKORIGIN,x', listing[i+1]) > 0) and
        (pos(':STACKORIGIN,x', listing[i+6]) > 0) and
        (pos(':STACKORIGIN+STACKWIDTH,x', listing[i+2]) > 0) and
        (pos(':STACKORIGIN+STACKWIDTH,x', listing[i+7]) > 0) and
        (pos(':STACKORIGIN+STACKWIDTH*2,x', listing[i+3]) > 0) and
        (pos(':STACKORIGIN+STACKWIDTH*2,x', listing[i+8]) > 0) and
        (pos(':STACKORIGIN+STACKWIDTH*3,x', listing[i+4]) > 0) and
        (pos(':STACKORIGIN+STACKWIDTH*3,x', listing[i+9]) > 0) then
     begin

       listing[i+11] := #9'lda ' + GetString(i+4);
       listing[i+12] := #9'cmp ' + GetString(i+9);

       listing[i+14] := #9'lda ' + GetString(i+3);
       listing[i+15] := #9'cmp ' + GetString(i+8);

       listing[i+17] := #9'lda ' + GetString(i+2);
       listing[i+18] := #9'cmp ' + GetString(i+7);

       listing[i+20] := #9'lda ' + GetString(i+1);
       listing[i+21] := #9'cmp ' + GetString(i+6);

       listing[i+1] := '';
       listing[i+2] := '';
       listing[i+3] := '';
       listing[i+4] := '';

       listing[i+6] := '';
       listing[i+7] := '';
       listing[i+8] := '';
       listing[i+9] := '';

       exit(false);
     end;


    if ldy_1(i) and										// ldy #1				; 0
       lda(i+1) and (lda_stack(i+1) = false) and						// lda 					; 1
       cmp(i+2) and (cmp_stack(i+2) = false) and						// cmp					; 2
       bne(i+3) and										// bne					; 3
       lda(i+4) and (lda_stack(i+4) = false) and						// lda 					; 4
       cmp(i+5) and (cmp_stack(i+5) = false) and						// cmp					; 5
       bne(i+6) and										// bne					; 6
       lda(i+7) and (lda_stack(i+7) = false) and						// lda 					; 7
       cmp(i+8) and (cmp_stack(i+8) = false) and						// cmp					; 8
       bne(i+9) and										// bne					; 9
       lda(i+10) and (lda_stack(i+10) = false) and						// lda 					; 10
       cmp(i+11) and (cmp_stack(i+11) = false) and						// cmp					; 11
       lab_a(i+12) then										//@					; 12
     begin

       if SKIP(i+13) and							// SKIP				; 13
          SKIP(i+14) and							// SKIP				; 14
          dey(i+15) and								// dey				; 15
          lab_a(i+16) and							//@				; 16
          dex(i+17) then							// dex				; 17
      	begin
	 listing[i+17] := listing[i+16];
	 listing[i+16] := listing[i+15];
	 listing[i+15] := listing[i+14];
	 listing[i+14] := listing[i+13];
	 listing[i+13] := listing[i+12];
	 listing[i+12] := listing[i+11];
	 listing[i+11] := listing[i+10];
	 listing[i+10] := listing[i+9];
	 listing[i+9] := listing[i+8];
	 listing[i+8] := listing[i+7];
	 listing[i+7] := listing[i+6];
	 listing[i+6] := listing[i+5];
	 listing[i+5] := listing[i+4];
	 listing[i+4] := listing[i+3];
	 listing[i+3] := listing[i+2];
	 listing[i+2] := listing[i+1];
	 listing[i+1] := listing[i];

	 listing[i] := #9'dex';

	 exit(false);
      	end;

       if SKIP(i+13) and							// SKIP				; 13
          dey(i+14) and								// dey				; 14
          lab_a(i+15) and							//@				; 15
          dex(i+16) then							// dex				; 16
      	begin
	 listing[i+16] := listing[i+15];
	 listing[i+15] := listing[i+14];
	 listing[i+14] := listing[i+13];
	 listing[i+13] := listing[i+12];
	 listing[i+12] := listing[i+11];
	 listing[i+11] := listing[i+10];
	 listing[i+10] := listing[i+9];
	 listing[i+9] := listing[i+8];
	 listing[i+8] := listing[i+7];
	 listing[i+7] := listing[i+6];
	 listing[i+6] := listing[i+5];
	 listing[i+5] := listing[i+4];
	 listing[i+4] := listing[i+3];
	 listing[i+3] := listing[i+2];
	 listing[i+2] := listing[i+1];
	 listing[i+1] := listing[i];

	 listing[i] := #9'dex';

	 exit(false);
      	end;

     end;


// -----------------------------------------------------------------------------
//	WORD
// -----------------------------------------------------------------------------

    if //inx(i) and										// inx					; 0
       mva(i+1) and 										// mva .. :STACKORIGIN,x		; 1
       mva(i+2) and										// mva .. :STACKORIGIN+STACKWIDTH,x	; 2
       inx(i+3) and										// inx					; 3
       mva(i+4) and 										// mva .. :STACKORIGIN,x		; 4
       mva(i+5) and										// mva .. :STACKORIGIN+STACKWIDTH,x	; 5
       ldy_1(i+6) and										// ldy #1				; 6
       (listing[i+7] = #9'lda :STACKORIGIN-1+STACKWIDTH,x') and					// lda :STACKORIGIN-1+STACKWIDTH,x	; 7
       (listing[i+8] = #9'cmp :STACKORIGIN+STACKWIDTH,x') and					// cmp :STACKORIGIN+STACKWIDTH,x	; 8
       bne(i+9) and										// bne @+				; 9
       (listing[i+10] = #9'lda :STACKORIGIN-1,x') and						// lda :STACKORIGIN-1,x			; 10
       (listing[i+11] = #9'cmp :STACKORIGIN,x') then						// cmp :STACKORIGIN,x			; 11
     if (pos(':STACKORIGIN,x', listing[i+1]) > 0) and
        (pos(':STACKORIGIN,x', listing[i+4]) > 0) and
        (pos(':STACKORIGIN+STACKWIDTH,x', listing[i+2]) > 0) and
        (pos(':STACKORIGIN+STACKWIDTH,x', listing[i+5]) > 0) then
     begin

       listing[i+7] := #9'lda ' + GetString(i+2);
       listing[i+8] := #9'cmp ' + GetString(i+5);

       listing[i+10] := #9'lda ' + GetString(i+1);
       listing[i+11] := #9'cmp ' + GetString(i+4);

       listing[i+1] := '';
       listing[i+2] := '';

       listing[i+4] := '';
       listing[i+5] := '';

       exit(false);
     end;


    if (mva(i) = false) and									//~mva					; 0
       inx(i+1) and										// inx					; 1
       mva(i+2) and 										// mva .. :STACKORIGIN,x		; 2
       mva(i+3) and										// mva .. :STACKORIGIN+STACKWIDTH,x	; 3
       ldy_1(i+4) and										// ldy #1				; 4
       (listing[i+5] = #9'lda :STACKORIGIN-1+STACKWIDTH,x') and					// lda :STACKORIGIN-1+STACKWIDTH,x	; 5
       (listing[i+6] = #9'cmp :STACKORIGIN+STACKWIDTH,x') and					// cmp :STACKORIGIN+STACKWIDTH,x	; 6
       bne(i+7) and										// bne @+				; 7
       (listing[i+8] = #9'lda :STACKORIGIN-1,x') and						// lda :STACKORIGIN-1,x			; 8
       (listing[i+9] = #9'cmp :STACKORIGIN,x') then						// cmp :STACKORIGIN,x			; 9
     if (pos(':STACKORIGIN,x', listing[i+2]) > 0) and
        (pos(':STACKORIGIN+STACKWIDTH,x', listing[i+3]) > 0) then
     begin

       listing[i+6] := #9'cmp ' + GetString(i+3);

       listing[i+9] := #9'cmp ' + GetString(i+2);

       listing[i+2] := '';
       listing[i+3] := '';

       exit(false);
     end;


    if (mva(i) = false) and									//~mva					; 0
       mva(i+1) and 										// mva .. :STACKORIGIN,x		; 1
       mva(i+2) and										// mva .. :STACKORIGIN+STACKWIDTH,x	; 2
       ldy_1(i+3) and										// ldy #1				; 3
       (listing[i+4] = #9'lda :STACKORIGIN-1+STACKWIDTH,x') and					// lda :STACKORIGIN-1+STACKWIDTH,x	; 4
       (listing[i+5] = #9'cmp :STACKORIGIN+STACKWIDTH,x') and					// cmp :STACKORIGIN+STACKWIDTH,x	; 5
       bne(i+6) and										// bne @+				; 6
       (listing[i+7] = #9'lda :STACKORIGIN-1,x') and						// lda :STACKORIGIN-1,x			; 7
       (listing[i+8] = #9'cmp :STACKORIGIN,x') then						// cmp :STACKORIGIN,x			; 8
     if (pos(':STACKORIGIN,x', listing[i+1]) > 0) and
        (pos(':STACKORIGIN+STACKWIDTH,x', listing[i+2]) > 0) then
     begin

       listing[i+5] := #9'cmp ' + GetString(i+2);

       listing[i+8] := #9'cmp ' + GetString(i+1);

       listing[i+1] := '';
       listing[i+2] := '';

       exit(false);
     end;




    if lab_a(i+6) and										//@					; 6

       ldy_1(i) and										// ldy #1				; 0
       lda(i+1) and (lda_stack(i+1) = false) and						// lda 					; 1
       cmp(i+2) and (cmp_stack(i+2) = false) and						// cmp					; 2
       bne(i+3) and										// bne					; 3
       lda(i+4) and (lda_stack(i+4) = false) and						// lda 					; 4
       cmp(i+5) and (cmp_stack(i+5) = false) then						// cmp					; 5
     begin

       if SKIP(i+7) and								// SKIP				; 7
          SKIP(i+8) and								// SKIP				; 8
          dey(i+9) and								// dey				; 9
          lab_a(i+10) and							//@				; 10
          dex(i+11) then							// dex				; 11
	begin
	 listing[i+11] := listing[i+10];
	 listing[i+10] := listing[i+9];
	 listing[i+9] := listing[i+8];
	 listing[i+8] := listing[i+7];
	 listing[i+7] := listing[i+6];
	 listing[i+6] := listing[i+5];
	 listing[i+5] := listing[i+4];
	 listing[i+4] := listing[i+3];
	 listing[i+3] := listing[i+2];
	 listing[i+2] := listing[i+1];
	 listing[i+1] := listing[i];

	 listing[i] := #9'dex';

	 exit(false);
      	end;


       if SKIP(i+7) and								// SKIP				; 7
          dey(i+8) and								// dey				; 8
          lab_a(i+9) and							//@				; 9
          dex(i+10) then							// dex				; 10
	begin
	 listing[i+10] := listing[i+9];
	 listing[i+9] := listing[i+8];
	 listing[i+8] := listing[i+7];
	 listing[i+7] := listing[i+6];
	 listing[i+6] := listing[i+5];
	 listing[i+5] := listing[i+4];
	 listing[i+4] := listing[i+3];
	 listing[i+3] := listing[i+2];
	 listing[i+2] := listing[i+1];
	 listing[i+1] := listing[i];

	 listing[i] := #9'dex';

	 exit(false);
      	end;

     end;


// -----------------------------------------------------------------------------
//	BOOLEAN
// -----------------------------------------------------------------------------

    if //inx(i) and										// inx					; 0
       mva(i+1) and										// mva   :STACKORIGIN,x			; 1
       ldy_1(i+2) and										// ldy #1				; 2
       (listing[i+3] = #9'lda :STACKORIGIN,x') and 						// lda :STACKORIGIN,x			; 3
       beq(i+4) then										// beq					; 4
     if (pos(':STACKORIGIN,x', listing[i+1]) > 0) then
     begin
       listing[i+3] := #9'lda ' + GetString(i+1);

       listing[i+1] := '';

       exit(false);
     end;


// -----------------------------------------------------------------------------
//	BYTE
// -----------------------------------------------------------------------------

    if //inx(i) and										// inx					; 0
       mva(i+1) and										// mva   :STACKORIGIN,x			; 1
       inx(i+2) and										// inx					; 2
       mva(i+3) and										// mva   :STACKORIGIN,x			; 3
       ldy_1(i+4) and										// ldy #1				; 4
       (listing[i+5] = #9'lda :STACKORIGIN-1,x') and 						// lda :STACKORIGIN-1,x			; 5
       (listing[i+6] = #9'cmp :STACKORIGIN,x') then 						// cmp :STACKORIGIN,x			; 6
     if (pos(':STACKORIGIN,x', listing[i+1]) > 0) and
        (pos(':STACKORIGIN,x', listing[i+3]) > 0) then
     begin
       listing[i+5] := #9'lda ' + GetString(i+1);
       listing[i+6] := #9'cmp ' + GetString(i+3);

       listing[i+1] := '';

       listing[i+3] := '';

       exit(false);
     end;


    if //inx(i) and										// inx					; 0
       mva(i+1) and										// mva   :STACKORIGIN,x			; 1
       dex(i+2) and										// dex					; 2
       mwy_bp2(i+3) and										// mwy .. :bp2				; 3
       ldy_im(i+4) and										// ldy #				; 4
       (listing[i+5] = #9'mva (:bp2),y :STACKORIGIN+2,x') and					// mva (:bp2),y :STACKORIGIN+2,x	; 5
       (listing[i+6] = #9'lda :STACKORIGIN+1,x') and 						// lda :STACKORIGIN+1,x			; 6
       (listing[i+7] = #9'cmp :STACKORIGIN+2,x') then 						// cmp :STACKORIGIN+2,x			; 7
     if (pos(':STACKORIGIN,x', listing[i+1]) > 0) then
     begin
       listing[i+6] := #9'lda ' + GetString(i+1);
       listing[i+7] := #9'cmp ' + GetString(i+5);

       listing[i+1] := '';

       listing[i+5] := '';

       exit(false);
     end;


    if ldy_1(i) and										// ldy #1				; 0
       lda(i+1) and (lda_stack(i+1) = false) and						// lda 					; 1
       SKIP(i+2) and										// SKIP					; 2
       dey(i+3) and										// dey					; 3
       lab_a(i+4) and										//@					; 4
       dex(i+5) then										// dex					; 5
     begin
	listing[i+5] := listing[i+4];
	listing[i+4] := listing[i+3];
	listing[i+3] := listing[i+2];
	listing[i+2] := listing[i+1];
	listing[i+1] := listing[i];

	listing[i] := #9'dex';

	exit(false);
     end;


    if ldy_1(i) and										// ldy #1				; 0
       lda(i+1) and (lda_stack(i+1) = false) and						// lda 					; 1
       cmp(i+2) and (cmp_stack(i+2) = false) and						// cmp					; 2
       SKIP(i+3) and										// SKIP					; 3
       SKIP(i+4) and										// SKIP					; 4
       dey(i+5) and										// dey					; 5
       lab_a(i+6) and										//@					; 6
       dex(i+7) then										// dex					; 7
     begin
	listing[i+7] := listing[i+6];
	listing[i+6] := listing[i+5];
	listing[i+5] := listing[i+4];
	listing[i+4] := listing[i+3];
	listing[i+3] := listing[i+2];
	listing[i+2] := listing[i+1];
	listing[i+1] := listing[i];

	listing[i] := #9'dex';

	exit(false);
     end;


    if ldy_1(i) and										// ldy #1				; 0
       lda(i+1) and (lda_stack(i+1) = false) and						// lda 					; 1
       cmp(i+2) and (cmp_stack(i+2) = false) and						// cmp					; 2
       SKIP(i+3) and										// SKIP					; 3
       dey(i+4) and										// dey					; 4
       lab_a(i+5) and										//@					; 5
       dex(i+6) then										// dex					; 6
     begin
	listing[i+6] := listing[i+5];
	listing[i+5] := listing[i+4];
	listing[i+4] := listing[i+3];
	listing[i+3] := listing[i+2];
	listing[i+2] := listing[i+1];
	listing[i+1] := listing[i];

	listing[i] := #9'dex';

	exit(false);
     end;



// -----------------------------------------------------------------------------
//	INTEGER
// -----------------------------------------------------------------------------




// -----------------------------------------------------------------------------
//	SMALLINT
// -----------------------------------------------------------------------------

    if //inx(i) and										// inx					; 0
       mva(i+1) and										// mva   :STACKORIGIN,x			; 1
       mva(i+2) and										// mva   :STACKORIGIN+STACKWIDTH,x	; 2
       inx(i+3) and										// inx					; 3
       mva(i+4) and										// mva   :STACKORIGIN,x			; 4
       mva(i+5) and										// mva   :STACKORIGIN+STACKWIDTH,x	; 5
       ldy_1(i+6) and										// ldy #1				; 6
       (listing[i+7] = #9'.LOCAL') and								// .LOCAL				; 7
       (listing[i+8] = #9'lda :STACKORIGIN-1+STACKWIDTH,x') and 				// lda :STACKORIGIN-1+STACKWIDTH,x	; 8
       (listing[i+9] = #9'sub :STACKORIGIN+STACKWIDTH,x') and					// sub :STACKORIGIN+STACKWIDTH,x	; 9
       (listing[i+10] = #9'bne L4') and								// bne L4				; 10
       (listing[i+11] = #9'lda :STACKORIGIN-1,x') and 						// lda :STACKORIGIN-1,x			; 11
       (listing[i+12] = #9'cmp :STACKORIGIN,x') then						// cmp :STACKORIGIN,x			; 12
     if (pos(':STACKORIGIN,x', listing[i+1]) > 0) and
        (pos(':STACKORIGIN,x', listing[i+4]) > 0) and
        (pos(':STACKORIGIN+STACKWIDTH,x', listing[i+2]) > 0) and
        (pos(':STACKORIGIN+STACKWIDTH,x', listing[i+5]) > 0) then
     begin

       listing[i+8] := #9'lda ' + GetString(i+2);
       listing[i+9] := #9'sub ' + GetString(i+5);

       listing[i+11] := #9'lda ' + GetString(i+1);
       listing[i+12] := #9'cmp ' + GetString(i+4);

       listing[i+1] := '';
       listing[i+2] := '';

       listing[i+4] := '';
       listing[i+5] := '';

       exit(false);

     end;


    if (listing[i+16] = #9'.ENDL') and								// .ENDL				; 16

       ldy_1(i) and										// ldy #1				; 0
       (listing[i+1] = #9'.LOCAL') and								// .LOCAL				; 1
       lda(i+2) and (lda_stack(i+2) = false) and						// lda E+1				; 2
       sub(i+3) and (sub_stack(i+3) = false) and						// sub					; 3
       (listing[i+4] = #9'bne L4') and								// bne L4				; 4
       lda(i+5) and (lda_stack(i+5) = false) and						// lda E				; 5
       cmp(i+6) and (cmp_stack(i+6) = false) and						// cmp					; 6
       (listing[i+7] = #9'beq L5') and								// beq L5				; 7
       (listing[i+8] = #9'lda #$00') and							// lda #$00				; 8
       (listing[i+9] = #9'adc #$FF') and							// adc #$FF				; 9
       (listing[i+10] = #9'ora #$01') and							// ora #$01				; 10
       (listing[i+11] = #9'bne L5') and								// bne L5				; 11
       (listing[i+12] = 'L4'#9'bvc L5') and							//L4 bvc L5				; 12
       (listing[i+13] = #9'eor #$FF') and							// eor #$FF				; 13
       (listing[i+14] = #9'ora #$01') and							// ora #$01				; 14
       (listing[i+15] = 'L5') then								//L5					; 15
     begin

       if SKIP(i+17) and							// SKIP				; 17
          SKIP(i+18) and							// SKIP				; 18
          dey(i+19) and								// dey				; 19
          lab_a(i+20) and							//@				; 20
          dex(i+21) then							// dex				; 21
	begin
	 listing[i+21] := listing[i+20];
	 listing[i+20] := listing[i+19];
	 listing[i+19] := listing[i+18];
	 listing[i+18] := listing[i+17];
	 listing[i+17] := listing[i+16];
	 listing[i+16] := listing[i+15];
	 listing[i+15] := listing[i+14];
	 listing[i+14] := listing[i+13];
	 listing[i+13] := listing[i+12];
	 listing[i+12] := listing[i+11];
	 listing[i+11] := listing[i+10];
	 listing[i+10] := listing[i+9];
	 listing[i+9] := listing[i+8];
	 listing[i+8] := listing[i+7];
	 listing[i+7] := listing[i+6];
	 listing[i+6] := listing[i+5];
	 listing[i+5] := listing[i+4];
	 listing[i+4] := listing[i+3];
	 listing[i+3] := listing[i+2];
	 listing[i+2] := listing[i+1];
	 listing[i+1] := listing[i];

	 listing[i] := #9'dex';

	 exit(false);
	end;


       if SKIP(i+17) and							// SKIP				; 17
          dey(i+18) and								// dey				; 18
          lab_a(i+19) and							//@				; 19
          dex(i+20) then							// dex				; 20
	begin
	 listing[i+20] := listing[i+19];
	 listing[i+19] := listing[i+18];
	 listing[i+18] := listing[i+17];
	 listing[i+17] := listing[i+16];
	 listing[i+16] := listing[i+15];
	 listing[i+15] := listing[i+14];
	 listing[i+14] := listing[i+13];
	 listing[i+13] := listing[i+12];
	 listing[i+12] := listing[i+11];
	 listing[i+11] := listing[i+10];
	 listing[i+10] := listing[i+9];
	 listing[i+9] := listing[i+8];
	 listing[i+8] := listing[i+7];
	 listing[i+7] := listing[i+6];
	 listing[i+6] := listing[i+5];
	 listing[i+5] := listing[i+4];
	 listing[i+4] := listing[i+3];
	 listing[i+3] := listing[i+2];
	 listing[i+2] := listing[i+1];
	 listing[i+1] := listing[i];

	 listing[i] := #9'dex';

	 exit(false);
	end;

     end;


// -----------------------------------------------------------------------------
//	SHORTINT
// -----------------------------------------------------------------------------

    if //inx(i) and										// inx					; 0
       mva(i+1) and										// mva   :STACKORIGIN,x			; 1
       inx(i+2) and										// inx					; 2
       mva(i+3) and										// mva   :STACKORIGIN,x			; 3
       ldy_1(i+4) and										// ldy #1				; 4
       (listing[i+5] = #9'.LOCAL') and								// .LOCAL				; 5
       (listing[i+6] = #9'lda :STACKORIGIN-1,x') and 						// lda :STACKORIGIN-1,x			; 6
       (listing[i+7] = #9'sub :STACKORIGIN,x') then 						// sub :STACKORIGIN,x			; 7
     if (pos(':STACKORIGIN,x', listing[i+1]) > 0) and
        (pos(':STACKORIGIN,x', listing[i+3]) > 0) then
     begin
       listing[i+6] := #9'lda ' + GetString(i+1);
       listing[i+7] := #9'sub ' + GetString(i+3);

       listing[i+1] := '';

       listing[i+3] := '';

       exit(false);
     end;


    if (listing[i+9] = #9'.ENDL') and								// .ENDL				; 9

       ldy_1(i) and										// ldy #1				; 0
       (listing[i+1] = #9'.LOCAL') and								// .LOCAL				; 1
       lda(i+2) and (lda_stack(i+2) = false) and						// lda E				; 2
       sub(i+3) and (sub_stack(i+3) = false) and						// sub					; 3
       (listing[i+4] = #9'beq L5') and								// beq L5				; 4
       (listing[i+5] = #9'bvc L5') and								// bvc L5				; 5
       (listing[i+6] = #9'eor #$FF') and							// eor #$FF				; 6
       (listing[i+7] = #9'ora #$01') and							// ora #$01				; 7
       (listing[i+8] = 'L5') then								//L5					; 8
     begin

       if SKIP(i+10) and							// SKIP				; 10
          SKIP(i+11) and							// SKIP				; 11
          dey(i+12) and								// dey				; 12
          lab_a(i+13) and							//@				; 13
          dex(i+14) then							// dex				; 14
	begin
	 listing[i+14] := listing[i+13];
	 listing[i+13] := listing[i+12];
	 listing[i+12] := listing[i+11];
	 listing[i+11] := listing[i+10];
	 listing[i+10] := listing[i+9];
	 listing[i+9] := listing[i+8];
	 listing[i+8] := listing[i+7];
	 listing[i+7] := listing[i+6];
	 listing[i+6] := listing[i+5];
	 listing[i+5] := listing[i+4];
	 listing[i+4] := listing[i+3];
	 listing[i+3] := listing[i+2];
	 listing[i+2] := listing[i+1];
	 listing[i+1] := listing[i];

	 listing[i] := #9'dex';

	 exit(false);
      	end;


       if SKIP(i+10) and							// SKIP				; 10
          dey(i+11) and								// dey				; 11
          lab_a(i+12) and							//@				; 12
          dex(i+13) then							// dex				; 13
	begin
	 listing[i+13] := listing[i+12];
	 listing[i+12] := listing[i+11];
	 listing[i+11] := listing[i+10];
	 listing[i+10] := listing[i+9];
	 listing[i+9] := listing[i+8];
	 listing[i+8] := listing[i+7];
	 listing[i+7] := listing[i+6];
	 listing[i+6] := listing[i+5];
	 listing[i+5] := listing[i+4];
	 listing[i+4] := listing[i+3];
	 listing[i+3] := listing[i+2];
	 listing[i+2] := listing[i+1];
	 listing[i+1] := listing[i];

	 listing[i] := #9'dex';

	 exit(false);
      	end;

     end;


end;		// function