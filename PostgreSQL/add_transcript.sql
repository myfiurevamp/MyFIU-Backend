/* Records transcript in database. 
 * Tables affected: transcript, taken_course.
 * Use this function for every transcript. 
 * NOTE: ALL COURSES MUST BE ATTACHED TO TRANSCRIPT IN ONE FUNCTION 
 * CALL. COURSES MAY NOT BE ATTACHED TO A TRANSCRIPT IN ANOTHER QUERY 
 * BECAUSE TRANSCRIPT_ID WHICH IS AUTO-INCREMENTED WILL MOST LIKELY NOT 
 * BE KNOWN.
 */
BEGIN; -- begin transaction for atomicity e.g. record entire transcript or abort.


/* Lock tables. Prevent any sort of access from any other transaction.
 * May not be necessary; however, extra security measures are taken
 * to make sure of data validity. 
 */
LOCK TABLE student_transcript, taken_course IN ACCESS EXCLUSIVE MODE;

DO
$$
	DECLARE 
		_returned_t_id student_transcript.transcript_id%TYPE; -- returned transcript ID
		_time student_transcript.t_time_recorded%TYPE;
		_panther_id student_transcript.panther_id%TYPE;
		_major_1 student_transcript.major_1%TYPE;
		_major_2 student_transcript.major_2%TYPE;
		_minor student_transcript.minor%TYPE;
		_gpa student_transcript.gpa%TYPE;
	
	BEGIN -- begin function
	
		/* Initialize these variables before sending this query. */
		_time := 'NOW'; -- DO NOT CHANGE WITHOUT REQUEST!
		_panther_id := '5170455';
		_major_1 := 'Computer Science';
		_major_2 := NULL;
		_minor := 'Psychology';
		_gpa := 3.77;
	
		/* Insert transcript tuple.
		* DEFAULT: used incremented static serial type transcript_id.
		* 'NOW': get current time of recording.
		*/
		INSERT INTO student_transcript (t_time_recorded, 
			panther_id, major_1, major_2, minor, gpa) 
			VALUES (_time, _panther_id, _major_1, 
			_major_2, _minor, _gpa) 
			RETURNING transcript_id INTO _returned_t_id;

		/* Insert classes associated with transcript .
		 * May need loop to automatically generate tuple for each
		 * course.
		 */
		INSERT INTO taken_course(transcript_id, course_num, semester_taken,
			grade_received, passed) 
			VALUES (_returned_t_id, 'CEN 4010', 'Spring 2016', 'A-', 't'),
			(_returned_t_id, 'CNT 4713', 'Spring 2016' , 'A', 't'),
			(_returned_t_id, 'COP 5725', 'Spring 2016', 'A', 't'),
			(_returned_t_id, 'CAP 5771', 'Spring 2016', 'C-', 'f');
		
	END; -- end function
	$$ language plpgsql;

COMMIT; -- commit transcation and free locks (automatic)