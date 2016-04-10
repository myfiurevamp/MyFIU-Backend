/* Validates guest's credentials.
 * Tables affected: N/A.
 * If result is >= 1, credentials are authentic.
 */	
SELECT COUNT(*)
FROM app_user NATURAL JOIN guest
WHERE app_user.username = 'guest' AND app_user.pw = 'ilovemyfiurevamp';