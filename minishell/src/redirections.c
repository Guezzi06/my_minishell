/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguezzi <aguezzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:20:23 by aguezzi           #+#    #+#             */
/*   Updated: 2023/06/26 16:28:58 by aguezzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Au niveau des redirections, il faut creer une fonction qui va stocker le fd_in au fur et a mesure qu'on rencontre des chevrons <,
un seul fd_in sera stocke et renouvele a chaque fois qu'on croise un <,
si jamas on trouve une erreur sur l'ouverture d'un fichier, alors on s'arrete la et on met un message d'erreur
Meme chose pour les chevrons fermantes >, où on va devoir creer une fonction qui va stocker un fd_out.

Au niveau des pipes, il faut creer un child process des que j'en croise un |, pour que j'execute les instructions en parallele,
si jamais je trouve une erreur sur un noeud de pipe, alors les autres noeuds ne seront pas touchees par cette erreur et continueront
leur execution independamment

En cas de syntax error, par exemple un double pipe | |, alors si avant cette error j'ai un heredoc, celui est pris en compte et ouvert puis
on peut ecrire a l'interieur comme si l'execution etait en suspens, une fois qu on a fini d'y ecrire alors l'execution reprend puis on affiche
notre syntax error*/