/* Validates superuser's credentials.
 * Tables affected: N/A
 * If result is >= 1, credentials are authentic.
 */	
SELECT COUNT(*)
FROM app_user NATURAL JOIN superuser
WHERE app_user.username = 'admin' AND app_user.pw = 
'someadminpassword';