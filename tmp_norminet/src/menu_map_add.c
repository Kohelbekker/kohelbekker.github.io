#include "wolf3d.h"

int	ft_chek_dfile(char *str, char *f)
{
	int i;
	int c;

	i = 0;
	c = 0;
	while (str[i++] != '\0')
		;
	if (i <= 5 || str[0] == '.')
		return (0);
	i -= 5;
	while (str[i++] == f[c++] && str[i] != '\0')
		;
	if (c != 4)
		return (0);
	return (1);
}

char *add_map_name(char *str)
{
	char *name;
	int i;
	int j;

	i = ft_strlen(str) - 4;
	if (i > 7)
		i = 9;
	name = (char *)malloc(sizeof(char) * (i + 1));
	j = 0;
	while (str[j] != '.' && j <= 6)
	{
		name[j] = str[j];
		j++;
	}
	if (i == 9)
	{
		name[7] = '.';
		name[8] = '.'; 
		name[9] = '.';
		j = 10;
	}
	name[j] = '\0';
	return (name);
}

void load_maps(t_maps *m_l)
{
	int j;
	int i;
	int fddir;
	DIR *dfd;
	struct dirent *dp;

	i = 0;
	j = 0;
	fddir = open("maps", O_DIRECTORY);
	if (fddir == -1)
		ft_putendl("Map dir NotFound");
	dfd = opendir("maps");
	while((dp = readdir(dfd)) != NULL)
	{
		if (ft_chek_dfile(dp->d_name, ".map") == 1)
			i++;
	}
	m_l->max_maps = i - 1;
	rewinddir(dfd);
	m_l->map_path = (char **)malloc(sizeof(char *) * (i + 1));
	m_l->map_name = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while((dp = readdir(dfd)) != NULL)
	{
		if (ft_chek_dfile(dp->d_name, ".map") == 1)
		{
			i = ft_strlen(dp->d_name);
			m_l->map_name[j] = add_map_name(dp->d_name);
			i += ft_strlen("maps/");
			m_l->map_path[j] = (char *)malloc(sizeof(char) * i);
			m_l->map_path[j] = ft_strcat(m_l->map_path[j],"maps/");
			m_l->map_path[j] = ft_strcat(m_l->map_path[j], dp->d_name);
			j++;
		}
		i = 0;
	}
	closedir(dfd);
	close(fddir);
}

void	show_map_name(t_box *box, int c, int z)
{
	int ch = 1;
	int y = 304;
	SDL_Texture  *pic;

	while ((ch + box->map_list.c_list - 1) <= box->map_list.max_maps && ch <= 6)
	{
		if(z != ch && c != ch)
		{
			pic = renderText_blue(box->map_list.map_name[ch + box->map_list.c_list - 1],
				"ttf/mainfont.ttf", 35, box->rend);
			ApplySurface(944, y, 0, 0, pic, box->rend);
			y += 54;
			ch++;
		}
		else
		{
			y += 54;
			ch++;
		}
	}
	if ((ch + box->map_list.c_list - 1) == (box->map_list.max_maps + 1))
		box->map_list.l_f = 1;
	else
		box->map_list.l_f = 0;
}

void	ifc_map_name(t_box *box, int c, int z)
{
	int ch = 1;
	int y = 304;
	SDL_Texture  *pic;

	while ((ch + box->map_list.c_list - 1) <= box->map_list.max_maps && ch <= 6)
	{
		if(z == ch && c != ch)
		{
			pic = renderText_red(box->map_list.map_name[ch + box->map_list.c_list - 1],
				"ttf/mainfont.ttf", 35, box->rend);
			ApplySurface(944, y, 0, 0, pic, box->rend);
			y += 54;
			box->start = ch + box->map_list.c_list - 1;
			ch++;
		}
		else
		{
			y += 54;
			ch++;
		}
	}
}

void	ifp_map_name(t_box *box, int c, int z)
{
	int ch = 1;
	int y = 304;
	SDL_Texture  *pic;

	while ((ch + box->map_list.c_list - 1) <= box->map_list.max_maps && ch <= 6)
	{
		if(z != ch && c == ch)
		{
			pic = renderText_purp(box->map_list.map_name[ch + box->map_list.c_list - 1],
				"ttf/mainfont.ttf", 35, box->rend);
			ApplySurface(944, y, 0, 0, pic, box->rend);
			y += 54;
			ch++;
		}
		else
		{
			y += 54;
			ch++;
		}
	}
}

void	ifcnp_map_name(t_box *box, int c, int z)
{
	int ch = 1;
	int y = 304;
	SDL_Texture  *pic;

	while ((ch + box->map_list.c_list - 1) <= box->map_list.max_maps && ch <= 6)
	{
		if(z == ch && c == ch)
		{
			pic = renderText_red(box->map_list.map_name[ch + box->map_list.c_list - 1],
				"ttf/mainfont.ttf", 35, box->rend);
			ApplySurface(944, y, 0, 0, pic, box->rend);
			y += 54;
			box->start = ch + box->map_list.c_list - 1;
			ch++;
		}
		else
		{
			y += 54;
			ch++;
		}
	}
}

void if_b_or_n(t_box *box, int x, int y, int *z, int *c)
{
	if ((x > 945 && x < 1075) && (y > 640 && y < 680))
	{
		if (box->map_list.c_list > 0)
		{
			box->map_list.c_list -= 6;
			*z = -1;
			*c = -1;
		}
	}
	else if ((x > 1095 && x < 1230) && (y > 640 && y < 680))
	{
		if (box->map_list.l_f == 0)
		{
			box->map_list.c_list += 6;
			*z = -1;
			*c = -1;
		}
	}
}