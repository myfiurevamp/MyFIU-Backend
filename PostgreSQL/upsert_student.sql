/* Adds a new student or updates student info if student already exists
 * in database.
 * Tables affected: app_user, student.
 * Put NULL if values for unecessary attributes are not known such as 
 * fb_username.
 */
BEGIN; -- begin transaction for atomicity e.g. add/update student or abort.

	DO
	$$
	
	DECLARE
		hits smallint; -- number of times student appears in table
		_panther_id student.panther_id%TYPE; 
		_fiu_username student.fiu_username%TYPE; 
		_fb_username student.fb_username%TYPE; 
		_full_name student.full_name%TYPE;
		
	BEGIN -- begin function
	
	/* Initialize these variables before sending this query. */
	_panther_id := '5170455'; -- Panther ID
	_fiu_username := 'jrodr074'; -- myAccounts username (FIU)
	_fb_username := 'jorgerodr95@hotmail.com'; -- Facebook username
	_full_name := 'Jorge Rodriguez'; -- full name
	
	/* Check if student exists as app_user in database. */
	SELECT COUNT(*) INTO hits
	FROM app_user
	WHERE app_username = _panther_id;
	
	/* If student does not exist as app_user, add to table. */
	IF hits = 0 THEN
		INSERT INTO app_user (app_username, pw) VALUES(p_id, NULL);
	END IF;
	
	/* Check if student exists as a student in database. */
	SELECT COUNT(*) INTO hits
	FROM student
	WHERE panther_id = _panther_id;
	
	/* If student does not exist as student, add to table; however,
	 * he/she does exist as student, update info in table.
	 */
	IF hits = 0 THEN
		INSERT INTO student (panther_id, fiu_username, fb_username, 
		full_name)
		VALUES (_panther_id, _fiu_username, _fb_username, 
			_full_name);
	ELSE 
		UPDATE student SET (panther_id, fiu_username, fb_username, 
		full_name) = (_panther_id, _fiu_username, _fb_username, _full_name)
		WHERE panther_id = _panther_id;
	END IF;
			
	END; -- end function
	$$ language plpgsql;
		
COMMIT; -- commit transaction