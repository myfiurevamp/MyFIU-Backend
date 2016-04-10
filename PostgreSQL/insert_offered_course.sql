/* Inserts offered course.
 * Tables affected: offered_course.
 * semester_offered format: (Fall | Spring | Summer A | Summer B |
 * Summer C) (Year) e.g. Fall 2016, Summer C 2016.
 * category determined by course prefix e.g. COP = Computer Programming,
 * CNT = Computer Networks, CAP = Computer Applications.
 * NOTE: DO NOT CHANGE 'NOW' WITHOUT REQUEST!
 */
INSERT INTO offered_course (course_num, oc_time_recorded,
	semester_offered, location_offered, instructor_name, oc_credits,
	course_name, category)
	VALUES ('CNT 4713', 'NOW', 'Spring 2016', 'Modesto A. Maidique 
	Campus', 'Leonardo Bobadilla', 3, 'Net-centric Computing', 
	'Computer Networks'),
	('MAD 3512', 'NOW', 'Summer B 2016', 'Modesto A. Maidique Campus',
	'Dev Roy', 3, 'Theory of Algorithms', 'Discrete Mathematics');
	